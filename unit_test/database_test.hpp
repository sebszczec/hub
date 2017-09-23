#ifndef __DATABASE_TEST_HPP
#define __DATABASE_TEST_HPP

#include <gtest/gtest.h>
#include "database.hpp"
#include <iostream>

using database::Database;

class DatabaseTest : public testing::Test
{
public:
    Database * sut;
public:
    DatabaseTest()
    {
        this->sut = Database::GetInstance();
    }

    ~DatabaseTest()
    {
        Database::ClearInstance();
    }
};

TEST_F(DatabaseTest, CheckInstance)
{
    EXPECT_FALSE(Database::GetInstance() == nullptr);
}

#endif
