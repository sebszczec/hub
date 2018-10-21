#ifndef __SYSTEM_HPP
#define __SYSTEM_HPP

#include <chrono>
#include <ctime>
#include <mutex>
#include "account_manager.hpp"
#include "command_manager.hpp"
#include "configuration_manager.hpp"
#include "context_manager.hpp"
#include "database.hpp"
#include "memory_manager.hpp"
#include "logger.hpp"

using namespace std::chrono;

namespace machine
{

class System
{
    System() = delete;
    ~System() = delete;

    static account::AccountManager * _accountManager;
    static ConfigurationManager * _configurationManager;
    static database::Database * _database;
    static commands::CommandManager * _commandManager;
    static network::ContextManager * _contetxManager;
    static MemoryManager * _memoryManager;
    static Logger * _logger;

    static system_clock::time_point _timeNow;
    static void RegisterCommands();
public:
    using DelayUS = std::chrono::duration<int, std::micro>;

    static bool Start();
    static void Stop();

    static account::AccountManager * GetAccountManager();
    static commands::CommandManager * GetCommandManager();
    static ConfigurationManager * GetConfigurationManager();
    static network::ContextManager * GetContextManager();
    static database::Database * GetDatabase();
    static Logger * GetLogger();
    static MemoryManager * GetMemoryManager();

    static system_clock::duration UpTime();

     // Help methods for UTs
     static void InitializeMembersForUT()
     {
        _configurationManager = new ConfigurationManager();
        if (!System::_configurationManager->LoadResources())
        {
            return;
        }

        _accountManager = new account::AccountManager();
        _commandManager = new commands::CommandManager();

        _contetxManager = new network::ContextManager();
        _database = new database::Database();
        _logger = new Logger();
        _memoryManager = new MemoryManager();

        _logger->Initilize("hub_ut.log", 1, machine::LogLevel::Debug);
        System::_accountManager->RefreshWithDB();
     }

     static void FreeMembersForUT()
     {
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

        if (_commandManager != nullptr)
        {
            delete _commandManager;
            _commandManager = nullptr;
        }

        if (_contetxManager != nullptr)
        {
            delete _contetxManager;
            _contetxManager = nullptr;
        }

        if (_logger != nullptr)
        {
            _logger->ClearResources();
            delete _logger;
            _logger = nullptr;
        }

        if (_memoryManager != nullptr)
        {
            delete _memoryManager;
            _memoryManager = nullptr;
        }
     }
};

} // namespace machine

#endif 