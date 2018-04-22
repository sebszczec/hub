#ifndef __SYSTEM_HPP
#define __SYSTEM_HPP

#include <chrono>
#include <ctime>
#include "command_manager.hpp"
#include "configuration_manager.hpp"
#include "context_manager.hpp"
#include "database.hpp"

using namespace std::chrono;

namespace machine
{

class System
{
    System() = delete;
    ~System() = delete;

    static ConfigurationManager * _configurationManager;
    static database::Database * _database;
    static commands::CommandManager * _commandManager;
    static network::ContextManager * _contetxManager;

    static system_clock::time_point _timeNow;
    static void RegisterCommands();
public:
    using DelayUS = std::chrono::duration<int, std::micro>;

    static bool Start();
    static void Stop();

    static commands::CommandManager * GetCommandManager();
    static ConfigurationManager * GetConfigurationManager();
    static network::ContextManager * GetContextManager();
    static database::Database * GetDatabase();

    static system_clock::duration UpTime();

     // Help methods for UTs
     static void InitializeMembersForUT()
     {
         _commandManager = new commands::CommandManager();
        _configurationManager = new ConfigurationManager();
        _contetxManager = new network::ContextManager();
        _database = new database::Database();
     }

     static void FreeMembersForUT()
     {
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
     }
};

} // namespace machine

#endif 