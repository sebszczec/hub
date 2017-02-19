#include "telnet_connection.hpp"
#include "logger.hpp"
#include "command_manager.hpp"

string TelnetConnection::ExtractCommand(const string& message)
{
    auto position = message.find(' ');
    if (position == string::npos)
    {
        position = message.find('\r');
    }

    if (position == string::npos)
    {
        throw TelnetConnection::CommandParseException();
    }

    return message.substr(0, position);
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
        auto command = this->ExtractCommand(message);
        Logger::LogDebug("TelnetConnection: got command " + command);

        string result = "";
        if (CommandManager::ExecuteCommand(command, result))
        {
            Logger::LogDebug("TelnetConnection: command execution result: " + result);
            *this->_stream << result << "\n";
        }
    }
}
