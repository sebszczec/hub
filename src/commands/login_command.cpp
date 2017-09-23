#include "login_command.hpp"

namespace commands
{

string LoginCommand::Register()
{
    return this->_name;
}

string LoginCommand::PrintHelp()
{
    return "login to system";
}

bool LoginCommand::Execute(const CommandArgument &)
{
    return true;
}

string LoginCommand::GetResult()
{
    return "access granted.";
}

} // namespace commands
