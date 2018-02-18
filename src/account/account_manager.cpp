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
            auto & key = row["name"];
            this->_userInDB[key].Username = key;
            this->_userInDB[key].Password = row["password"];
        }
    }

    bool AccountManager::ValidateUser(const std::string & name, const std::string & password)
    {
        auto iterator = this->_userInDB.find(name);
        if (iterator == this->_userInDB.end())
        {
            Logger::LogError("AccountManager: user " + name + " does not exist in DB");
            return false;
        }

        if (iterator->second.Password.compare(password) != 0)
        {
            Logger::LogError("AccountManager: wrong password for user " + name);
            return false;
        }

        Logger::Log("AccountManager: user " + name + " validated");

        return true;
    }

    void AccountManager::ClearUserCache()
    {
        this->_userInDB.clear();
    }

}