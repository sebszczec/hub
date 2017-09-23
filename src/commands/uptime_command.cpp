#include "uptime_command.hpp"
#include "system.hpp"
#include "logger.hpp"
#include <sstream>

using namespace machine;

namespace commands
{

string UptimeCommand::Register()
{
    return this->_name;
}
    
string UptimeCommand::PrintHelp()
{
    return "shows how long applications works";
}
    
bool UptimeCommand::Execute(const CommandArgument &)
{
    Logger::LogDebug(this->_name + " called");

    auto uptime = System::UpTime();

    auto milliseconds = std::chrono::duration_cast<UptimeCommand::Milliseconds>(uptime).count();
    auto seconds = std::chrono::duration_cast<UptimeCommand::Seconds>(uptime).count();
    auto minutes = std::chrono::duration_cast<UptimeCommand::Minutes>(uptime).count();
    auto hours = std::chrono::duration_cast<UptimeCommand::Hours>(uptime).count();

    auto _minutes = minutes - 60 * hours;
    auto _seconds = seconds - 60 * minutes;
    auto _milliseconds = milliseconds - 1000 * seconds;

    std::stringstream stream; 
    stream << std::to_string(hours) << " hours, " << std::to_string(_minutes) << " minutes, " << std::to_string(_seconds) << " seconds, " << std::to_string(_milliseconds) << " milliseconds";
    this->_result = stream.str();

    return true;
}
    
string UptimeCommand::GetResult()
{
    return this->_result;
}

} // namespace commands
