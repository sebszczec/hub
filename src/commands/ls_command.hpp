#ifndef __LS_COMMAND_HPP
#define __LS_COMMAND_HPP

#include "icommand.hpp"
#include <string>

namespace commands
{

class LsCommand : public ICommand
{
private:
    const string _name = ".uptime";
    string _result = "";
public:
    LsCommand() = default;
    ~LsCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
    account::AccessLevel::Level GetAccessLevel() override;
};

} // namespace commands

#endif