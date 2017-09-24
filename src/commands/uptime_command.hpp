#ifndef __UPTIME_COMMAND_HPP
#define __UPTIME_COMMAND_HPP

#include "icommand.hpp"
#include <string>
#include <chrono>

namespace commands
{

class UptimeCommand : public ICommand
{
private:
    const string _name = ".uptime";
    string _result = "";
public:
    using Milliseconds = std::chrono::milliseconds;
    using Seconds = std::chrono::seconds;
    using Minutes = std::chrono::minutes;
    using Hours = std::chrono::hours;

    UptimeCommand() = default;
    ~UptimeCommand() = default;

    string Register() override;
    string PrintHelp() override;
    bool Execute(const CommandArgument &) override;
    string GetResult() override;
    account::AccessLevel::Level GetAccessLevel() override;
};

} // namespace commands

#endif
