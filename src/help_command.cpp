#include "help_command.hpp"
#include "command_manager.hpp"

string HelpCommand::Register()
{
    return ".help";
}

string HelpCommand::PrintHelp()
{
    return "Shows help info about command, i.e. .help <command>";
}

bool HelpCommand::Execute(const CommandArgument &arg)
{
    auto && size = arg.Args.size();
    if (size == 0)
    {
        this->_result = this->PrintHelp();
        return true;
    }

    if (size > 1)
    {
        this->_result = "Wrong argument number";
        return true;
    }

    auto commandManager = CommandManager::GetInstance();
    auto & command = arg.Args[0];
    if (!commandManager->GetCommandHelp(command, this->_result))
    {
        return false;
    }

    return true;
}

string HelpCommand::GetResult()
{
    return this->_result;
}
