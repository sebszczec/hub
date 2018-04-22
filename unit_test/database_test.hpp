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
        this->sut = new Database();
    }

    ~DatabaseTest()
    {
        delete this->sut;
    }
};


TEST_F(DatabaseTest, GetTableNoConnection)
{
    EXPECT_THROW(sut->GetTable("foobar"), database::NotDatabaseConnectionException);
}

TEST_F(DatabaseTest, GetNotExistingTable)
{
    sut->Connect();
    EXPECT_THROW(sut->GetTable("foobar"), database::SqlStatementException);
    sut->Disconnect();
}

TEST_F(DatabaseTest, GetUsersTable)
{
    sut->Connect();
    auto result = sut->GetTable("users");

    EXPECT_EQ(2, result.size());

    string id = "1";
    EXPECT_STREQ(id.c_str(), result[0]["id"].c_str());
    string name = "slaugh";
    EXPECT_STREQ(name.c_str(), result[0]["name"].c_str());
    string password = "seb666";
    EXPECT_STREQ(password.c_str(), result[0]["password"].c_str());

    id = "2";
    EXPECT_STREQ(id.c_str(), result[1]["id"].c_str());
    name = "sszczeci";
    EXPECT_STREQ(name.c_str(), result[1]["name"].c_str());
    password = "seb777";
    EXPECT_STREQ(password.c_str(), result[1]["password"].c_str());

    sut->Disconnect();
}

#endif
