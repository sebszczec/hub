#include "whoami_command.hpp"
#include "system.hpp"

using namespace machine;

namespace commands
{

string WhoamiCommand::Register()
{
    return this->_name;
}

string WhoamiCommand::PrintHelp()
{
    auto message = "displays who you are";
    return message;
}

bool WhoamiCommand::Execute(const CommandArgument & commandArgument)
{
    auto logger = System::GetLogger();

    logger->LogDebug(this->_name + " called");

    this->_result = commandArgument.Context->GetUser().GetName();
    return true;
}

string WhoamiCommand::GetResult()
{
    return this->_result;
}

account::AccessLevel::Level WhoamiCommand::GetAccessLevel()
{
    return account::AccessLevel::Level::User;
}

} // namespace commands