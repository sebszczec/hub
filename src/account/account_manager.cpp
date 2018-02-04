#include "account_manager.hpp"
#include "database.hpp"
#include "logger.hpp"

using database::Database;
using database::SqlResult;
using machine::Logger;

namespace account
{
    void AccountManager::RefreshWithDB()
    {
        Logger::Log("AccountManager: refreshing user base with DB");
        auto instance = Database::GetInstance();

        if (!instance->Connect())
        {
            Logger::LogError("AccountManager: unable to connect to DB");
            return;
        }
    
        auto result = instance->GetTable("users");
        instance->Disconnect();

        for (auto & row : result)
        {
            this->_userInDB[row["name"]].Username = row["name"];
            this->_userInDB[row["name"]].Password = row["password"];
        }
    }
}