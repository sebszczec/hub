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
        Logger::Log("AccountManager: refreshing user base with database");
        auto instance = Database::GetInstance();
        auto result = instance->GetTable("users");
    }
}