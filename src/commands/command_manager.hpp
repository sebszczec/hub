#ifndef __COMMAND_MANAGER_HPP
#define __COMMAND_MANAGER_HPP

#include "icommand.hpp"
#include <map>
#include <string>

namespace commands
{

class CommandExecutionResult
{
public:
    bool Success = false;
    string Result = "";
    string ErrorMessage = "";
};

class CommandManager
{
private:
    void ClearAllCommands();

    std::map<std::string, commands::ICommand *> _commands;

    commands::ICommand * SearchCommand(const string & command);

public:
    CommandManager() = default;
    ~CommandManager();

    void RegisterCommand(commands::ICommand * command);
    bool ExecuteCommand(const string & command, const commands::CommandArgument &, CommandExecutionResult & result);
    bool GetCommandHelp(const string & command, string & result);
};

} // namepace commands

#endif
