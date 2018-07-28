#ifndef __LOGOUT_COMMAND_HPP
#define __LOGOUT_COMMAND_HPP

#include "icommand.hpp"
#include <string>

using namespace std;

namespace commands
{

class LogoutCommand : public ICommand
{
private:
    const string _name = ".logout";
    string _result = "";
public:
    LogoutCommand() = default;
    ~LogoutCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
    account::AccessLevel::Level GetAccessLevel() override;
};

} // namespace commands

#endif