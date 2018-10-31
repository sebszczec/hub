#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>
#include "system.hpp"
#include "configuration_manager.hpp"
#include "icommand.hpp"
#include "worker.hpp"
#include "timer.hpp"
#include "signal_handler.hpp"
#include "mobile_messages.hpp"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include "tcp_server.hpp"
#include "tcp_ssl_server.hpp"
#include "telnet_connection.hpp"
#include "mobile_connection.hpp"
#include "strings.hpp"

using namespace network;
using namespace machine;

using boost::asio::ip::tcp;

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

    TcpServer<TelnetConnection> telnetServer(::machine::string::telnet, System::GetConfigurationManager()->GetResource(CMV::TelnetPort).ToInt());
    
    tools::Worker telnetWorker(false);
    telnetWorker.StartAsync([&telnetServer] () {telnetServer.Run();});

    TcpServer<MobileConnection> mobileServer(::machine::string::mobile, System::GetConfigurationManager()->GetResource(CMV::MobilePort).ToInt());
    
    tools::Worker mobileWorker(false);
    mobileWorker.StartAsync([&mobileServer] () {mobileServer.Run();});

    // TcpSSLServer<TelnetConnection> telnetSSLServer("SSL", 5555);
    
    // tools::Worker telnetSSLWorker(false);
    // telnetSSLWorker.StartAsync([&telnetSSLServer] () {telnetSSLServer.Run();});

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

