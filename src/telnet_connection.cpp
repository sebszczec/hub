#include "telnet_connection.hpp"
#include "logger.hpp"
#include "command_manager.hpp"

bool TelnetConnection::ExtractCommand(const string& message, string & result)
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
    return true;
}

void TelnetConnection::HandleData(Block * block)
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
        if (!this->ExtractCommand(message, command))
        {
            Logger::LogError("TelnetConnection: cannot extract command from " + message);
            return;
        }

        Logger::LogDebug("TelnetConnection: got command " + command);

        string result = "";
        if (CommandManager::GetInstance()->ExecuteCommand(command, result))
        {
            Logger::LogDebug("TelnetConnection: command execution result: " + result);
            *this->_stream << result << "\n";
        }
    }
}
