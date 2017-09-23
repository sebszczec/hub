#ifndef __LOGIN_COMMAND_HPP
#define __LOGIN_COMMAND_HPP

#include "icommand.hpp"
#include <string>

using namespace std;

class LoginCommand : public ICommand
{
private:
    const string _name = ".login";
    string _result = "";
public:
    LoginCommand() = default;
    ~LoginCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
};

#endif
