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

    // Telnet server
    TcpServer<TelnetConnection> telnetServer(
        ::machine::string::telnet, 
        System::GetConfigurationManager()->GetResource(CMV::TelnetPort).ToInt(),
        false);
    
    tools::Worker telnetWorker(false);

    if (System::GetConfigurationManager()->GetResource(CMV::TelnetEnabled).ToBool())
    {
        telnetWorker.StartAsync([&telnetServer] () {telnetServer.Run();});
    }

    // Mobile server
    TcpServer<MobileConnection> mobileServer(
        ::machine::string::mobile, 
        System::GetConfigurationManager()->GetResource(CMV::MobilePort).ToInt(),
        false);
    
    tools::Worker mobileWorker(false);

    if (System::GetConfigurationManager()->GetResource(CMV::MobileEnabled).ToBool())
    {
        mobileWorker.StartAsync([&mobileServer] () {mobileServer.Run();});
    }

    // Telnet SSL server
    TcpServer<TelnetConnection> telnetServerSSL(
        ::machine::string::telnet, 
        System::GetConfigurationManager()->GetResource(CMV::TelnetSSLPort).ToInt(),
        true);

    tools::Worker telnetWorkerSSL(false);

    if (System::GetConfigurationManager()->GetResource(CMV::TelnetSSLEnabled).ToBool())
    {
        telnetServerSSL.SetSSLServerCrtFile(System::GetConfigurationManager()->GetResource(CMV::SSLCRTFile).ToString());
        telnetServerSSL.SetSSLServerKeyFile(System::GetConfigurationManager()->GetResource(CMV::SSLKeyFile).ToString());
        telnetServerSSL.SetSSLServerDhFile(System::GetConfigurationManager()->GetResource(CMV::SSLDhFile).ToString());
        telnetServerSSL.SetSSLPassword(System::GetConfigurationManager()->GetResource(CMV::SSLPassword).ToString());
          
        telnetWorkerSSL.StartAsync([&telnetServerSSL] () {telnetServerSSL.Run();});
    }

    /* The Big Loop */
    auto logger = System::GetLogger();
    while (true) 
    {
        /* Do some task here ... */
        (void)logger;  
        //logger->LogDebug("Standard loop");  
        sleep(1); /* wait 1 second */
    }

   exit(EXIT_SUCCESS);
}

