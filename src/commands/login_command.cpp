#include "login_command.hpp"
#include "logger.hpp"

using namespace machine;

namespace commands
{

string LoginCommand::Register()
{
    return this->_name;
}

string LoginCommand::PrintHelp()
{
    auto message = "login to system, usage: " + this->_name + " user password";
    return message;
}

bool LoginCommand::Execute(const CommandArgument & commandArgument)
{
    Logger::LogDebug(this->_name + " called");

    if (commandArgument.Args.size() < 2)
    {   
        auto errorMessage = "failed, not enough arguments";
        this->_result = errorMessage;
        Logger::LogError(this->_name + " " + errorMessage);
        return false;
    }
    else if (commandArgument.Args.size() > 2)
    {
        auto errorMessage = "failed, too many arguments";
        this->_result = errorMessage;
        Logger::LogError(this->_name + " " + errorMessage);
        return false;
    }

    this->_result = "access granted";
    return true;
}

string LoginCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level LoginCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::NotLogged;
}

} // namespace commands
