#ifndef __UPTIME_COMMAND_HPP
#define __UPTIME_COMMAND_HPP

#include "icommand.hpp"

class UptimeCommand : public ICommand
{
private:
    const string _name = ".uptime";
    const string _helpText = "Shows time how long service works on.\nUsage: " + _name + "\n";
public:
    UptimeCommand() = default;
    ~UptimeCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute() override;
    void * GetResult() override;
};

#endif
