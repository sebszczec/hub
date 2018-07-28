#include "logout_command.hpp"
#include "account_manager.hpp"
#include "system.hpp"

using namespace machine;
using namespace account;

namespace commands
{

string LogoutCommand::Register()
{
    return this->_name;
}

string LogoutCommand::PrintHelp()
{
    auto message = "logout from system";
    return message;
}

bool LogoutCommand::Execute(const CommandArgument & commandArgument)
{
    auto logger = System::GetLogger();

    logger->LogDebug(this->_name + " called");

    commandArgument.Context->GetUser().GetAccessLevel().SetLevel(account::AccessLevel::Level::NotLogged);
    this->_result = "logout successful";
    return true;
}

string LogoutCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level LogoutCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::User;
}

} // namespace commands