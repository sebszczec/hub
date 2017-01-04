#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "logger.hpp"
#include "configuration_manager.hpp"
#include "worker.hpp"

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
    daemon.Initilize();

    Worker worker(true, Worker::DelayMS(1000));
    worker.StartAsync([](string a){
        Logger::LogDebug("I am alive! " + a);
    },
    "TERROR");

    int a = 0;
    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */  
        Logger::LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */

        if (a++ == 5)
        {
            worker.Stop();
        }
    }

   exit(EXIT_SUCCESS);
}

