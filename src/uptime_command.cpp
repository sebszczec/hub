#include "uptime_command.hpp"

string UptimeCommand::Register()
{
    return this->_name;
}
    
string UptimeCommand::PrintHelp()
{
    return this->_helpText;
}
    
bool UptimeCommand::Execute()
{
    return false;
}
    
void * UptimeCommand::GetResult()
{
    return nullptr;
}