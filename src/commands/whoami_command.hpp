#ifndef __WHOAMI_COMMAND_HPP
#define __WHOAMI_COMMAND_HPP

#include "icommand.hpp"
#include <string>

using namespace std;

namespace commands
{

class WhoamiCommand : public ICommand
{
private:
    const string _name = ".whoami";
    string _result = "";
public:
    WhoamiCommand() = default;
    ~WhoamiCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
    account::AccessLevel::Level GetAccessLevel() override;
};

} // namespace commands

#endif
