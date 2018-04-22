#include "help_command.hpp"
#include "command_manager.hpp"
#include "logger.hpp"
#include "system.hpp"

using machine::Logger;
using machine::System;

namespace commands
{

string HelpCommand::Register()
{
    return ".help";
}

string HelpCommand::PrintHelp()
{
    return "shows help info about command, i.e. .help <command>";
}

bool HelpCommand::Execute(const CommandArgument &arg)
{
    Logger::LogDebug(this->_name + " called");

    auto && size = arg.Args.size();
    if (size == 0)
    {
        this->_result = this->PrintHelp();
        return true;
    }

    if (size > 1)
    {
        this->_result = "wrong argument number";
        return true;
    }

    auto commandManager = System::GetCommandManager();
    auto & command = arg.Args[0];
    if (!commandManager->GetCommandHelp(command, this->_result))
    {
        Logger::LogError(this->_name + " failed when processing");
        return false;
    }

    return true;
}

string HelpCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level HelpCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::NotLogged;
}

} // namespace commands
