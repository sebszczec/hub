#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "logger.hpp"
#include <libconfig.h++>
#include <iostream>
#include <iomanip>
#include <cstdlib>

int main()
{
    libconfig::Config config_file;

    try
    {
        config_file.readFile("settings.cfg");
    }
    catch (const libconfig::FileIOException &exception)
    {
        std::cerr << "I/O error while reading config file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch (const libconfig::ParseException &exception)
    {
        std::cerr << "Config file parse error at " << exception.getFile() << ":" << exception.getLine() << " - " << exception.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    Logger::Initilize("hub.log", 1, LogLevel::Debug);

    Daemon daemon;
    daemon.Initilize();
    
    Logger::LogDebug("1 DEBUG should be visible");
    Logger::Log("1 INFO should be visible");
    Logger::LogError("1 ERROR should be visible");

    Logger::SetLogLevel(LogLevel::Info);
    Logger::LogDebug("2 DEBUG should NOT be visible");
    Logger::Log("2 INFO should be visible");
    Logger::LogError("2 ERROR should be visible");

    Logger::SetLogLevel(LogLevel::Error);
    Logger::LogDebug("3 DEBUG should NOT be visible");
    Logger::Log("3 INFO should NOT be visible");
    Logger::LogError("3 ERROR should be visible");

    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */    
        sleep(30); /* wait 30 seconds */
    }

   exit(EXIT_SUCCESS);
}

