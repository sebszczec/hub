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
#include "memory_manager.hpp"
#include "telnet_server.hpp"

using namespace commands;
using namespace database;
using namespace network;
using namespace tools;

namespace machine
{

ConfigurationManager * System::_configurationManager = nullptr;
Database * System::_database = nullptr;

system_clock::time_point System::_timeNow = system_clock::now();

bool System::Start()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    System::_configurationManager = new ConfigurationManager();
    System::_database = new Database();
    
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

    return true;
}

void System::Stop()
{
    MemoryManager::GetInstance()->DumpMemory();

    if (_database != nullptr)
        delete _database;
    
    if (_configurationManager != nullptr)
        delete _configurationManager;

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
    System::GetCommandManager()->RegisterCommand(new UptimeCommand());
    System::GetCommandManager()->RegisterCommand(new LoginCommand());
    System::GetCommandManager()->RegisterCommand(new HelpCommand());
}

CommandManager * System::GetCommandManager()
{
    return CommandManager::GetInstance2();
}

ConfigurationManager * System::GetConfigurationManager()
{
    return System::_configurationManager;
}

Database * System::GetDatabase()
{
    return System::_database;
}

} // namespace machine
