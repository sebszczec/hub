#ifndef __DATABASE_HPP
#define __DATABASE_HPP
#include <sqlite3.h>

class Database
{
private:
    Database();
    ~Database();

    sqlite3 * _database;

    static Database * _instance;

public:

    static Database * GetInstance();
    static void ClearInstance();
};

#endif
