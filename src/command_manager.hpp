#ifndef __COMMAND_MANAGER_HPP
#define __COMMAND_MANAGER_HPP

#include "icommand.hpp"
#include <map>
#include <string>

class CommandManager
{
private:
    static std::map<std::string, ICommand *> _commands;
public:
    CommandManager() = delete;
    ~CommandManager() = delete;

    static void RegisterCommand(ICommand * command);
    static void ClearAllCommands();
};

#endif
