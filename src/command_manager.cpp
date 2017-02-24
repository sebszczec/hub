#include "command_manager.hpp"
#include "logger.hpp"

CommandManager * CommandManager::_instance = nullptr;

CommandManager::~CommandManager()
{
    this->ClearAllCommands();
}

void CommandManager::ClearInstance()
{
    if (CommandManager::_instance != nullptr)
    {
        delete CommandManager::_instance;
        CommandManager::_instance = nullptr;
    }
}

CommandManager * CommandManager::GetInstance()
{
    if (CommandManager::_instance == nullptr)
    {
        CommandManager::_instance = new CommandManager();
    }

    return CommandManager::_instance;
}

void CommandManager::RegisterCommand(ICommand * command)
{
    auto key = command->Register();
    this->_commands[key] = command;

    Logger::LogDebug("CommandManager: command " + key + " registered");
}

void CommandManager::ClearAllCommands()
{
    Logger::Log("CommandManager: cleaning all commands");

    for (auto & pair : this->_commands)
    {
        delete pair.second;
    }

    this->_commands.clear();
}

bool CommandManager::ExecuteCommand(const string & command, string & result)
{
    auto item = this->_commands.find(command);
    if (item == this->_commands.end())
    {
        Logger::LogError("CommandManager: command " + command + " not found");
        return false;
    }

    if (!item->second->Execute())
    {
        Logger::LogError("CommandManager: command " + command + " executed with error");
        return false;
    }

    result = item->second->GetResult();

    return true;
}