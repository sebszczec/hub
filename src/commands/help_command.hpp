#ifndef __HELP_COMMAND_HPP
#define __HELP_COMMAND_HPP

#include "icommand.hpp"

class HelpCommand : public ICommand
{
private:
    const string _name = ".help";
    string _result = "";
public:

    HelpCommand() = default;
    ~HelpCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
};


#endif
