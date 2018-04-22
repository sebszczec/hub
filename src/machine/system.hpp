#ifndef __SYSTEM_HPP
#define __SYSTEM_HPP

#include <chrono>
#include <ctime>
#include "configuration_manager.hpp"
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

    static system_clock::time_point _timeNow;
    static void RegisterCommands();
public:
    using DelayUS = std::chrono::duration<int, std::micro>;

    static bool Start();
    static void Stop();

    static ConfigurationManager * GetConfigurationManager();
    static database::Database * GetDatabase();

    static system_clock::duration UpTime();

     // Help methods for UTs
     static void InitializeMembersForUT()
     {
        _configurationManager = new ConfigurationManager();
        _database = new database::Database();
     }

     static void FreeMembersForUT()
     {
        if (_database != nullptr)
            delete _database;
    
        if (_configurationManager != nullptr)
            delete _configurationManager;
     }
};

} // namespace machine

#endif 