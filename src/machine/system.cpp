#include "system.hpp"
#include "configuration_manager.hpp"
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

system_clock::time_point System::_timeNow = system_clock::now();

bool System::Start()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    auto configurationManager = CM::GetInstance();
    
    if (!configurationManager->LoadResources())
    {
        return false;
    }

    Logger::Initilize(
    configurationManager->GetResource(CMV::LogFileName).ToString(), 
    configurationManager->GetResource(CMV::LogResolution).ToInt(), 
    (LogLevel)configurationManager->GetResource(CMV::LogLevel).ToInt());

    Daemon::Initilize(configurationManager->GetResource(CMV::IsDaemon).ToBool());
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
    ConfigurationManager::ClearInstance();
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

} // namespace machine
