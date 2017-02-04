#include "uptime_command.hpp"
#include "system.hpp"
#include "logger.hpp"

string UptimeCommand::Register()
{
    return this->_name;
}
    
string UptimeCommand::PrintHelp()
{
    return "Shows how long applications works";
}
    
bool UptimeCommand::Execute()
{
    Logger::LogDebug(this->_name + " called");

    auto uptime = System::UpTime();

    auto milliseconds = std::chrono::duration_cast<UptimeCommand::Milliseconds>(uptime).count();
    auto seconds = std::chrono::duration_cast<UptimeCommand::Seconds>(uptime).count();
    auto minutes = std::chrono::duration_cast<UptimeCommand::Minutes>(uptime).count();
    auto hours = std::chrono::duration_cast<UptimeCommand::Hours>(uptime).count();

    this->_result = std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes, " + std::to_string(seconds) + " seconds, " + std::to_string(milliseconds) + " milliseconds";

    return true;
}
    
string UptimeCommand::GetResult()
{
    return this->_result;
}