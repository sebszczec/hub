#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>
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
    daemon.Initilize( CM::GetResource(CMV::IsDaemon).ToBool());

    SignalHandler::RegisterExitSignals();

    Worker worker(true, Worker::DelayMS(500));
    worker.StartAsync([](){
        Logger::LogDebug("Keep alive message from worker.");
    });

    Timer timer(Worker::DelayMS(500), true);
    timer.StartAsync([](){
        Logger::LogDebug("Keep alive message from timer.");
    });

    using libsocket::inet_stream_server;

    string host = "127.0.0.1";
    string port = CM::GetResource(CMV::TelnetPort).ToString();

    inet_stream_server srv(host, port, LIBSOCKET_IPv4);

    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */  
        Logger::LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */
    }

   exit(EXIT_SUCCESS);
}

