#include "command_manager.hpp"
#include "logger.hpp"

std::map<std::string, ICommand *> CommandManager::_commands;

void CommandManager::RegisterCommand(ICommand * command)
{
    auto key = command->Register();
    CommandManager::_commands[key] = command;

    Logger::LogDebug("CommandManager: command " + key + " registered");
}

void CommandManager::ClearAllCommands()
{
    Logger::Log("CommandManager: cleaning all commands");

    for (auto pair : CommandManager::_commands)
    {
        delete pair.second;
    }

    CommandManager::_commands.clear();
}