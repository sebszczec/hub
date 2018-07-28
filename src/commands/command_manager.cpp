#include "command_manager.hpp"
#include "system.hpp"

using commands::ICommand;
using commands::CommandArgument;
using namespace machine;

namespace commands
{

CommandManager::~CommandManager()
{
    this->ClearAllCommands();
}

void CommandManager::RegisterCommand(ICommand * command)
{
    auto key = command->Register();
    this->_commands[key] = command;
    this->_commandNames.push_back(key);

    System::GetLogger()->LogDebug("CommandManager: command " + key + " registered");
}

void CommandManager::ClearAllCommands()
{
    System::GetLogger()->Log("CommandManager: cleaning all commands");

    for (auto & pair : this->_commands)
    {
        delete pair.second;
    }

    this->_commands.clear();
    this->_commandNames.clear();
}

ICommand * CommandManager::SearchCommand(const string & command)
{
    auto item = this->_commands.find(command);
    if (item == this->_commands.end())
    {
        System::GetLogger()->LogError("CommandManager: command " + command + " not found");
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

    if (found->GetAccessLevel() != arg.Context->GetUser().GetAccessLevel().GetLevel())
    {
        System::GetLogger()->LogError("CommandManager: no access to run " + command);
        result.ErrorMessage = "no access to run " + command;
        result.Success = false;
        return false;
    }

    if (!found->Execute(arg))
    {
        System::GetLogger()->LogError("CommandManager: command " + command + " executed with error");
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

std::vector<std::string> CommandManager::GetRegisteredCommands()
{
    return this->_commandNames;
}

} // namespace commands

