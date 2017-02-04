#include "system.hpp"
#include "configuration_manager.hpp"
#include "logger.hpp"
#include "daemon.hpp"
#include "signal_handler.hpp"

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
