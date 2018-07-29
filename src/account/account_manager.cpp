#include "account_manager.hpp"
#include "system.hpp"

using account::User;
using database::Database;
using database::SqlResult;
using machine::Logger;
using machine::System;

namespace account
{
    void AccountManager::RefreshWithDB()
    {
        auto logger = System::GetLogger();

        logger->Log("AccountManager: refreshing user base with DB");
        auto instance = System::GetDatabase();

        if (!instance->Connect())
        {
            logger->LogError("AccountManager: unable to connect to DB");
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

    bool AccountManager::ValidateUser(const std::string & name, const std::string & password, User & user)
    {
        auto logger = System::GetLogger();

        auto iterator = this->_userInDB.find(name);
        if (iterator == this->_userInDB.end())
        {
            logger->LogError("AccountManager: user " + name + " does not exist in DB");
            return false;
        }

        if (iterator->second.Password.compare(password) != 0)
        {
            logger->LogError("AccountManager: wrong password for user " + name);
            return false;
        }

        user.SetName(name);
        logger->Log("AccountManager: user " + name + " validated");

        return true;
    }

    void AccountManager::ClearUserCache()
    {
        this->_userInDB.clear();
    }

}