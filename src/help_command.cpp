#include "help_command.hpp"

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
    if (size == 0 || size > 1)
    {
        this->_result = this->PrintHelp();
        return false;
    }

    this->_result = "SUCCESS!";
    return true;
}

string HelpCommand::GetResult()
{
    return this->_result;
}
