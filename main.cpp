#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "system.hpp"
#include "configuration_manager.hpp"
#include "worker.hpp"
#include "timer.hpp"
#include "signal_handler.hpp"
#include "tcp_server.hpp"
#include "telnet_server.hpp"
#include "mobile_server.hpp"

using namespace network;
using namespace machine;

int main()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    if (!System::Start())
    {
        exit(EXIT_FAILURE);
    }

    // Worker worker(true, Worker::DelayMS(500));
    // worker.StartAsync([](){
    //     Logger::LogDebug("Keep alive message from worker.");
    // });

    // Timer timer(Worker::DelayMS(500), true);
    // timer.StartAsync([](){
    //     Logger::LogDebug("Keep alive message from timer.");
    // });

    TcpServer<TelnetServer> telnetServer(System::GetConfigurationManager()->GetResource(CMV::TelnetPort).ToString());
    tools::Worker telnetWorker(false);
    telnetWorker.StartAsync([&telnetServer] () { telnetServer.Start(); });

    TcpServer<MobileServer> mobileServer(System::GetConfigurationManager()->GetResource(CMV::MobilePort).ToString());
    tools::Worker mobileWorker(false);
    mobileWorker.StartAsync([&mobileServer] () { mobileServer.Start(); });

    /* The Big Loop */
    auto logger = System::GetLogger();
    while (true) 
    {
        /* Do some task here ... */  
        logger->LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */
    }

   exit(EXIT_SUCCESS);
}

