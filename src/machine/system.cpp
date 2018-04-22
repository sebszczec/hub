#include "system.hpp"
#include "logger.hpp"
#include "daemon.hpp"
#include "signal_handler.hpp"
#include "command_manager.hpp"
#include "context_manager.hpp"
#include "help_command.hpp"
#include "login_command.hpp"
#include "uptime_command.hpp"
#include "iasync.hpp"
#include "tcp_server.hpp"
#include "command_manager.hpp"
#include "database.hpp"
#include "memory_manager.hpp"
#include "telnet_server.hpp"

using namespace commands;
using namespace database;
using namespace network;
using namespace tools;

namespace machine
{

ConfigurationManager * System::_configurationManager = nullptr;

system_clock::time_point System::_timeNow = system_clock::now();

bool System::Start()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    System::_configurationManager = new ConfigurationManager();
    
    if (!System::_configurationManager->LoadResources())
    {
        return false;
    }

    Logger::Initilize(
        System::_configurationManager->GetResource(CMV::LogFileName).ToString(), 
        System::_configurationManager->GetResource(CMV::LogResolution).ToInt(), 
        (LogLevel)System::_configurationManager->GetResource(CMV::LogLevel).ToInt()
    );

    Daemon::Initilize(System::_configurationManager->GetResource(CMV::IsDaemon).ToBool());
    SignalHandler::RegisterExitSignals();
    System::RegisterCommands();
    
    auto db = Database::GetInstance();
    (void)db;

    return true;
}

void System::Stop()
{
    Database::ClearInstance();
    MemoryManager::GetInstance()->DumpMemory();

    CommandManager::ClearInstance();
    ContextManager::ClearInstance();
    TcpServer<TelnetServer>::StopAllInstances();
    IAsync::StopActiveJobs();
    MemoryManager::DeleteInstance();
    Logger::ClearResources();
}

system_clock::duration System::UpTime()
{
    return system_clock::now() - System::_timeNow;
}

void System::RegisterCommands()
{
    CommandManager::GetInstance()->RegisterCommand(new UptimeCommand());
    CommandManager::GetInstance()->RegisterCommand(new LoginCommand());
    CommandManager::GetInstance()->RegisterCommand(new HelpCommand());
}

ConfigurationManager * System::GetConfigurationManager()
{
    return System::_configurationManager;
}

} // namespace machine
