#include "command_manager.hpp"
#include "logger.hpp"

using commands::ICommand;
using commands::CommandArgument;
using namespace machine;

namespace commands
{

CommandManager * CommandManager::_instance = nullptr;

CommandManager::~CommandManager()
{
    this->ClearAllCommands();
}

CommandManager * CommandManager::GetInstance2()
{
    return CommandManager::GetInstance();
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

bool CommandManager::ExecuteCommand(const string & command, const CommandArgument &arg, CommandExecutionResult & result)
{
    auto found = SearchCommand(command);
    if (found == nullptr)
    {
        result.ErrorMessage = "command does not exist!";
        result.Success = false;
        return false;
    }

    if (found->GetAccessLevel() != arg.RequestorAccessLevel)
    {
        Logger::LogError("CommandManager: no access to run " + command);
        result.ErrorMessage = "no access to run " + command;
        result.Success = false;
        return false;
    }

    if (!found->Execute(arg))
    {
        Logger::LogError("CommandManager: command " + command + " executed with error");
        result.ErrorMessage = "error during command execution";
        result.Success = false;
        return false;
    }

    result.Result = found->GetResult();
    result.Success = true;

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

} // namespace commands

