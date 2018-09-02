#include "ls_command.hpp"
#include "system.hpp"

using namespace commands;

string LsCommand::Register()
{
    return this->_name;
}

string LsCommand::PrintHelp()
{
    return "shows all available commands";
}

bool LsCommand::Execute(const CommandArgument &)
{
    this->_result = "";
    auto commands = machine::System::GetCommandManager()->GetRegisteredCommands();

    for (auto command : commands)
    {
        this->_result += command + " ";
    }

    return true;
}

string LsCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level LsCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::NotLogged;
}
