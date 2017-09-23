#include "help_command.hpp"

string HelpCommand::Register()
{
    return ".help";
}

string HelpCommand::PrintHelp()
{
    return "Shows help info about command, i.e. .help <command>";
}

bool HelpCommand::Execute(const CommandArgument &)
{
    return true;
}

string HelpCommand::GetResult()
{
    return "";
}
