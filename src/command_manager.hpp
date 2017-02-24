#ifndef __COMMAND_MANAGER_HPP
#define __COMMAND_MANAGER_HPP

#include "icommand.hpp"
#include <map>
#include <string>

class CommandManager
{
private:
    CommandManager() = default;
    ~CommandManager();

    static CommandManager * _instance;
    std::map<std::string, ICommand *> _commands;

public:
    static CommandManager * GetInstance();

    void RegisterCommand(ICommand * command);
    void ClearAllCommands();
    bool ExecuteCommand(const string & command, string & result);
};

#endif
