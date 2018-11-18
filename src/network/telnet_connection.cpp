#include "telnet_connection.hpp"
#include "tcp_base.hpp"
#include "system.hpp"
#include "strings.hpp"

namespace network
{

using namespace machine; 

void TelnetConnection::Start()
{
    TcpConnection::Start();
    this->GetContext().GetUser().SetUserType(account::User::UserType::Telnet);

    auto message = ::machine::string::telnetWelcomeMessage;
    this->SendData(message.c_str(), message.size());
}

void TelnetConnection::ExtractParameters(const std::string & message, commands::CommandArgument & arg)
{

    auto position = message.find(' ');
    auto tempPos = 0;

    while (position != std::string::npos)
    {
        arg.Args.push_back(message.substr(tempPos, position - tempPos));
        tempPos = position + 1;
        position = message.find(' ', tempPos);
    }

    // and the last one
    position = message.find('\r', tempPos);

    // issue found when SSL enabled -> no carriage but only new line is present
    if (position == std::string::npos)
    {
        position = message.find('\n', tempPos);
    }
    
    if (position != std::string::npos)
    {
        arg.Args.push_back(message.substr(tempPos, position - tempPos));
    }
}

bool TelnetConnection::ExtractCommand(const std::string & message, std::string & result, commands::CommandArgument & arg)
{
    auto position = message.find(' ');
    if (position == std::string::npos)
    {
        position = message.find('\r');
    }

    // issue found when SSL enabled -> no carriage but only new line is present
    if (position == std::string::npos)
    {
        position = message.find('\n');
    }

    if (position == std::string::npos)
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
    auto id = std::to_string(this->GetContext().GetId());
    auto prefix = this->_parent.GetLoggingPrefix();

    auto length = this->_memoryBlock->GetPayloadLength();
    if (length == 0)
    {
        logger->LogError(prefix + "[" + id +  "]: memory block is empty");
        return;
    }

    char * payload = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());
    std::string message(payload, length);

    if (message[0] == '.')
    {
        std::string command = "";
        commands::CommandExecutionResult result;
        commands::CommandArgument arg;

        if (!this->ExtractCommand(message, command, arg))
        {
            logger->LogError(prefix + "[" + id +  "]: cannot extract command from " + message);
            return;
        }

        logger->LogDebug(prefix + "[" + id +  "]: got command " + command);

        arg.Context = this->_context;
        std::string message;
        if (System::GetCommandManager()->ExecuteCommand(command, arg, result))
        {
            logger->LogDebug(prefix + "[" + id +  "]: command execution result: " + result.Result);
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
    logger->LogDebug(prefix + "[" + id +  "]: sending to other users: " + message.substr(0, message.length() - 1));
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
