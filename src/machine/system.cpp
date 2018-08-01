#include "system.hpp"
#include "daemon.hpp"
#include "signal_handler.hpp"
#include "help_command.hpp"
#include "login_command.hpp"
#include "logout_command.hpp"
#include "ls_command.hpp"
#include "uptime_command.hpp"
#include "whoami_command.hpp"
#include "iasync.hpp"
#include "tcp_server.hpp"
#include "telnet_server.hpp"
#include "mobile_server.hpp"

using namespace account;
using namespace commands;
using namespace database;
using namespace network;
using namespace tools;

namespace machine
{

account::AccountManager * System::_accountManager = nullptr;
CommandManager * System::_commandManager = nullptr;
ConfigurationManager * System::_configurationManager = nullptr;
ContextManager * System::_contetxManager = nullptr;
Database * System::_database = nullptr;
Logger * System::_logger = nullptr;
MemoryManager * System::_memoryManager = nullptr;

system_clock::time_point System::_timeNow = system_clock::now();

std::mutex System::Mutex;

bool System::Start()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;
    System::_commandManager = new CommandManager();
    System::_configurationManager = new ConfigurationManager();
    System::_contetxManager = new ContextManager();
    System::_database = new Database();
    System::_accountManager = new AccountManager();
    System::_logger = new Logger();
    System::_memoryManager = new MemoryManager();
    
    if (!System::_configurationManager->LoadResources())
    {
        return false;
    }

    System::_logger->Initilize(
        System::_configurationManager->GetResource(CMV::LogFileName).ToString(), 
        System::_configurationManager->GetResource(CMV::LogResolution).ToInt(), 
        (LogLevel)System::_configurationManager->GetResource(CMV::LogLevel).ToInt()
    );

    Daemon::Initilize(System::_configurationManager->GetResource(CMV::IsDaemon).ToBool());
    SignalHandler::RegisterExitSignals();
    System::RegisterCommands();

    System::_accountManager->RefreshWithDB();

    return true;
}

void System::Stop()
{
    System::GetMemoryManager()->DumpMemory();

    if (_accountManager != nullptr)
    {
        delete _accountManager;
        _accountManager = nullptr;
    }

    if (_database != nullptr)
    {
        delete _database;
        _database = nullptr;
    }
    
    if (_configurationManager != nullptr)
    {
        delete _configurationManager;
        _configurationManager = nullptr;
    }

    if (_contetxManager != nullptr)
    {
        delete _contetxManager;
        _contetxManager = nullptr;
    }

    if (_commandManager != nullptr)
    {
        delete _commandManager;
        _commandManager = nullptr;
    }

    if (_memoryManager != nullptr)
    {
        delete _memoryManager;
        _memoryManager = nullptr;
    }

    TcpServer<TelnetServer>::StopAllInstances();
    TcpServer<MobileServer>::StopAllInstances();
    IAsync::StopActiveJobs();

    _logger->ClearResources();
    if (_logger != nullptr)
    {
        delete _logger;
        _logger = nullptr;
    }
}

system_clock::duration System::UpTime()
{
    return system_clock::now() - System::_timeNow;
}

void System::RegisterCommands()
{
    System::_commandManager->RegisterCommand(new HelpCommand());
    System::_commandManager->RegisterCommand(new LoginCommand());
    System::_commandManager->RegisterCommand(new LogoutCommand());
    System::_commandManager->RegisterCommand(new LsCommand());
    System::_commandManager->RegisterCommand(new UptimeCommand());
    System::_commandManager->RegisterCommand(new WhoamiCommand());
}

AccountManager * System::GetAccountManager()
{
    return System::_accountManager;
}

CommandManager * System::GetCommandManager()
{
    return System::_commandManager;
}

ConfigurationManager * System::GetConfigurationManager()
{
    return System::_configurationManager;
}

network::ContextManager * System::GetContextManager()
{
    return System::_contetxManager;
}

Database * System::GetDatabase()
{
    return System::_database;
}

Logger * System::GetLogger()
{
    return System::_logger;
}

MemoryManager * System::GetMemoryManager()
{
    return System::_memoryManager;
}

} // namespace machine
