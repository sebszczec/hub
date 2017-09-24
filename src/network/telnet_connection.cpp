#include "telnet_connection.hpp"
#include "logger.hpp"
#include "command_manager.hpp"
#include "connection_manager.hpp"

using machine::Logger;
using namespace::account;

namespace network
{

void TelnetConnection::ExtractParameters(const string &message, CommandArgument & arg)
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

bool TelnetConnection::ExtractCommand(const string& message, string & result, CommandArgument & arg)
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

void TelnetConnection::HandleData(machine::Block * block)
{
    if (block->GetPayloadLength() == 0)
    {
        return;
    }

    char * payload = reinterpret_cast<char *>(block->GetPayload());
    string message(payload, block->GetPayloadLength());

    if (message[0] == '.')
    {
        string command = "";
        commands::CommandExecutionResult result;
        commands::CommandArgument arg;

        if (!this->ExtractCommand(message, command, arg))
        {
            Logger::LogError("TelnetConnection: cannot extract command from " + message);
            return;
        }

        Logger::LogDebug("TelnetConnection: got command " + command);

        arg.RequestorAccessLevel = this->_context->GetUser().GetAccessLevel().GetLevel();
        if (commands::CommandManager::GetInstance()->ExecuteCommand(command, arg, result))
        {
            Logger::LogDebug("TelnetConnection: command execution result: " + result.Result);
            *this->_stream << command << ": " << result.Result << "\n";
        }
        else
        {
            *this->_stream << command << ": "<< result.ErrorMessage << "\n";
        }

        return;
    }

    // send message to others
    Logger::LogDebug("TelnetConnection: sending to other users: " + message.substr(0, message.length() - 1));
    for (auto & item : this->_parent->GetConnections())
    {
        if (item.first == this->_socketFd)
        {
            continue;
        }

        item.second->GetStream() << message;
    }
}

} // namespace network

