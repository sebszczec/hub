#include "system.hpp"
#include "configuration_manager.hpp"
#include "logger.hpp"
#include "daemon.hpp"
#include "signal_handler.hpp"

system_clock::time_point System::_timeNow = system_clock::now();

bool System::Start()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    if (!CM::LoadResources())
    {
        return false;
    }

    Logger::Initilize(
    CM::GetResource(CMV::LogFileName).ToString(), 
    CM::GetResource(CMV::LogResolution).ToInt(), 
    (LogLevel)CM::GetResource(CMV::LogLevel).ToInt());

    Daemon::Initilize(CM::GetResource(CMV::IsDaemon).ToBool());

    SignalHandler::RegisterExitSignals();

    return true;
}

system_clock::duration System::UpTime()
{
    return system_clock::now() - System::_timeNow;
}
