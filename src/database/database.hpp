#ifndef __DATABASE_HPP
#define __DATABASE_HPP

#include <vector>
#include <map>
#include <sqlite3.h>
#include <exception>
#include "db_exceptions.hpp"

using namespace std;

namespace database
{

using SqlResult = vector<map<string, string>>;

class Database
{
private:
    sqlite3 * _database;
    bool _connected = false;

    static Database * _instance;

    static Database * GetInstance();

public:
    Database() = default;
    ~Database() = default;

    static Database * GetInstance2();
    static void ClearInstance();

    bool Connect();
    void Disconnect();
    SqlResult GetTable(const string & tableName);
};

} // namespace database

#endif
