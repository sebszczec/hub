#include "database.hpp"
#include "logger.hpp"
#include <cstring>
#include <iostream>

using namespace machine;

namespace database
{

Database * Database::_instance = nullptr;

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
        Database::_instance = nullptr;
    } 
}

bool Database::Connect()
{
    if (this->_connected)
    {
        return true;
    }

    auto result = sqlite3_open("hub_database.db", &this->_database);
    
    if (result == 0)
    {
        Logger::Log("SQLite: connected to database");
        this->_connected = true;
        return true;
    }

    Logger::LogError("SQLite: can't connect to database");
    exit(EXIT_FAILURE);

    return false;
}

void Database::Disconnect()
{
    sqlite3_close(this->_database);
    Logger::Log("SQLite: disconnected from database");

    this->_connected = false;
}

SqlResult Database::GetTable(const string & tableName)
{
    if (!_connected)
    {
        Logger::LogError("SQLite: trying to get table " + tableName + "when not connected to database");
        throw NotDatabaseConnectionException();
    }

    SqlResult result;

    string sql = "SELECT * from " + tableName;
    auto query = sql.c_str();
    sqlite3_stmt * statement;

    auto db_result =  sqlite3_prepare_v2(this->_database, query, strlen(query), &statement, NULL);
    if (db_result != SQLITE_OK)
    {
        auto message = sqlite3_errmsg(this->_database);
        Logger::LogError("SQLite: wrong query, sqlite3 fault: " + string(message));
        sqlite3_finalize(statement);
        throw SqlStatementException(message);
    }

    auto columnCount = sqlite3_column_count(statement);

    while (true)
    {
        db_result = sqlite3_step(statement);
        if (db_result == SQLITE_DONE)
        {
            break;
        }

        if (db_result != SQLITE_ROW)
        {
            auto message = sqlite3_errmsg(this->_database);
            Logger::LogError("SQLite: error while reading, sqlite3 fault: " + string(message));
            sqlite3_finalize(statement);
            throw SqlFetchRowErrorException(message);
        }

        map<string, string> row;
        for (auto i = 0; i < columnCount; i++)
        {
            auto temp = (const char *)sqlite3_column_text(statement, i);
            row[sqlite3_column_name(statement, i)] = string(temp);
        }

        result.push_back(row);
    }

    sqlite3_finalize(statement);
    return result;
}

} // namespace database
