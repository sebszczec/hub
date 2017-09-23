#include "command_manager.hpp"
#include "logger.hpp"

using commands::ICommand;
using commands::CommandArgument;
using namespace machine;

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

ICommand * CommandManager::SearchCommand(const string & command)
{
    auto item = this->_commands.find(command);
    if (item == this->_commands.end())
    {
        Logger::LogError("CommandManager: command " + command + " not found");
        return nullptr;
    }

    return item->second;
}

bool CommandManager::ExecuteCommand(const string & command, const CommandArgument &arg, string & result)
{
    auto found = SearchCommand(command);
    if (found == nullptr)
    {
        return false;
    }

    if (!found->Execute(arg))
    {
        Logger::LogError("CommandManager: command " + command + " executed with error");
        return false;
    }

    result = found->GetResult();

    return true;
}

bool CommandManager::GetCommandHelp(const string & command, string & result)
{
    auto found = SearchCommand(command);
    if (found == nullptr)
    {
        return false;
    }

    result = found->PrintHelp();
    return true;
}