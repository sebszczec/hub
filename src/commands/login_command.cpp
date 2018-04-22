#include "login_command.hpp"
#include "account_manager.hpp"
#include "system.hpp"

using namespace machine;
using namespace account;

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
    auto logger = System::GetLogger();

    logger->LogDebug(this->_name + " called");

    if (commandArgument.Args.size() < 2)
    {   
        auto errorMessage = "failed, not enough arguments";
        this->_result = errorMessage;
        logger->LogError(this->_name + " " + errorMessage);
        return false;
    }
    else if (commandArgument.Args.size() > 2)
    {
        auto errorMessage = "failed, too many arguments";
        this->_result = errorMessage;
        logger->LogError(this->_name + " " + errorMessage);
        return false;
    }

    auto & name = commandArgument.Args[0];
    auto & password = commandArgument.Args[1];

    AccountManager accountManager;
    accountManager.RefreshWithDB();

    if (!accountManager.ValidateUser(name, password))
    {
       this->_result = "access danied"; 
       return true;
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
