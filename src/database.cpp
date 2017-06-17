#include "database.hpp"
#include "logger.hpp"

Database * Database::_instance = nullptr;

Database::Database()
{
    auto result = sqlite3_open("test.db", &this->_database);

    if (result == 0)
    {
        Logger::Log("SQLite: connected to database");
    }
    else
    {
        Logger::LogError("SQLite: can't connect to database");
        exit(EXIT_FAILURE);
    }
}

Database::~Database()
{
    sqlite3_close(this->_database);
    Logger::Log("SQLite: disconnected from database");
}

Database * Database::GetInstance()
{
    if (Database::_instance == nullptr)
    {
        Database::_instance = new Database();
    }

    return Database::_instance;
}

void Database::ClearInstance()
{
    if (Database::_instance != nullptr)
    {
        delete Database::_instance;
    } 
}