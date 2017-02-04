#include "command_manager.hpp"

std::map<std::string, ICommand *> CommandManager::_commands;

void CommandManager::RegisterCommand(ICommand * command)
{
    auto key = command->Register();
    CommandManager::_commands[key] = command;
}

void CommandManager::ClearAllCommands()
{
    for (auto pair : CommandManager::_commands)
    {
        delete pair.second;
    }

    CommandManager::_commands.clear();
}