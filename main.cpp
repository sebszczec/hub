#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "logger.hpp"
#include "configuration_manager.hpp"
#include "worker.hpp"
#include "timer.hpp"
#include "signal_handler.hpp"

int main()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    if (!CM::LoadResources())
    {
        return(EXIT_FAILURE);
    }
    
    Logger::Initilize(
        CM::GetResource(CMV::LogFileName).ToString(), 
        CM::GetResource(CMV::LogResolution).ToInt(), 
        (LogLevel)CM::GetResource(CMV::LogLevel).ToInt());

    Daemon daemon;
    if (CM::GetResource(CMV::IsDaemon).ToBool())
    {
        daemon.Initilize();
    }

    SignalHandler::RegisterExitSignals();

    Worker worker(true, Worker::DelayMS(1000));
    worker.StartAsync([](){
        Logger::LogDebug("Keep alive message.");
    });

    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */  
        Logger::LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */
    }

   exit(EXIT_SUCCESS);
}

