#include "ls_command.hpp"

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
    return false;
}

string LsCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level LsCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::NotLogged;
}
