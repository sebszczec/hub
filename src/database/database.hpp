#ifndef __DATABASE_HPP
#define __DATABASE_HPP

#include <list>
#include <map>
#include <sqlite3.h>

using namespace std;

namespace database
{

using SqlResult = list<map<string, void *>>;

class Database
{
private:
    Database();
    ~Database();

    sqlite3 * _database;

    static Database * _instance;

    list<map<string, string>> test;

public:

    static Database * GetInstance();
    static void ClearInstance();
};

} // namespace database

#endif
