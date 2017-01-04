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

    Worker worker;
    worker.StartAsync([](string a, string b){
        Logger::LogDebug("Worker ended job " + a + b);
    }, "argument text ", "second argument");

    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */    
        sleep(30); /* wait 30 seconds */
    }

   exit(EXIT_SUCCESS);
}

