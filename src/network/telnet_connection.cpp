#include "telnet_connection.hpp"
#include "tcp_connection_storage.hpp"
#include "system.hpp"

namespace network
{

using namespace machine; 

void TelnetConnection::Start()
{
    TcpConnection::Start();

    std::string message = "Welcome\n";
    this->SendData(message.c_str(), message.size());
}

void TelnetConnection::ExtractParameters(const string &message, commands::CommandArgument & arg)
{
    auto position = message.find(' ');
    auto tempPos = 0;

    while (position != string::npos)
    {
        arg.Args.push_back(message.substr(tempPos, position - tempPos));
        tempPos = position + 1;
        position = message.find(' ', tempPos);
    }

    // and the last one
    position = message.find('\r', tempPos);
    if (position != string::npos)
    {
        arg.Args.push_back(message.substr(tempPos, position - tempPos));
    }
}

bool TelnetConnection::ExtractCommand(const string& message, string & result, commands::CommandArgument & arg)
{
    auto position = message.find(' ');
    if (position == string::npos)
    {
        position = message.find('\r');
    }

    if (position == string::npos)
    {
        return false;
    }

    result = message.substr(0, position);
    this->ExtractParameters(message.substr(position + 1, message.size() - 1), arg);
    return true;
}

void TelnetConnection::HandleData()
{
    auto logger = System::GetLogger();

    auto length = this->_memoryBlock->GetPayloadLength();
    if (length == 0)
    {
        logger->LogError("TelnetConnection: memory block is empty");
        return;
    }

    char * payload = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());
    string message(payload, length);

    if (message[0] == '.')
    {
        string command = "";
        commands::CommandExecutionResult result;
        commands::CommandArgument arg;

        if (!this->ExtractCommand(message, command, arg))
        {
            logger->LogError("TelnetConnection: cannot extract command from " + message);
            return;
        }

        logger->LogDebug("TelnetConnection: got command " + command);

        arg.Context = this->_context;
        string message;
        if (System::GetCommandManager()->ExecuteCommand(command, arg, result))
        {
            logger->LogDebug("TelnetConnection: command execution result: " + result.Result);
            message = command + ": " + result.Result + "\n";
        }
        else
        {
            message = command + ": " + result.ErrorMessage + "\n";
        }

        this->SendData(reinterpret_cast<const void *>(message.c_str()), message.size());
        return;
    }

    // send message to others
    logger->LogDebug("TelnetConnection: sending to other users: " + message.substr(0, message.length() - 1));
    auto & connections = this->_parent.GetConnections();

    for (auto & item : connections)
    {
        if (item == shared_from_this())
        {
            continue;
        }

        item->SendData(reinterpret_cast<const void *>(message.c_str()), message.size());
    }
}

} // namespace network
