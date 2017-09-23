#ifndef __DATABASE_HPP
#define __DATABASE_HPP

#include <vector>
#include <map>
#include <sqlite3.h>
#include <exception>

using namespace std;

namespace database
{

class NotDatabaseConnectionException : public exception
{
};

class SqlStatementException : public exception
{
private:
    string _message;
public:
    SqlStatementException(const string & message)
    : _message(message)
    {

    }

    virtual const char * what() const throw() 
    {
        return this->_message.c_str();
    }

    virtual ~SqlStatementException() = default;
};

class SqlFetchRowErrorException : public exception
{
private:
    string _message;
public:
    SqlFetchRowErrorException(const string & message)
    : _message(message)
    {

    }

    virtual const char * what() const throw() 
    {
        return this->_message.c_str();
    }

    virtual ~SqlFetchRowErrorException() = default;
};

using SqlResult = vector<map<string, string>>;

class Database
{
private:
    Database() = default;
    ~Database() = default;

    sqlite3 * _database;
    bool _connected = false;

    static Database * _instance;

public:

    static Database * GetInstance();
    static void ClearInstance();

    bool Connect();
    void Disconnect();
    SqlResult GetTable(const string & tableName);
};

} // namespace database

#endif
