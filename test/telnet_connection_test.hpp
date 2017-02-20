#ifndef __TELNET_CONNECTION_TEST_HPP
#define __TELNET_CONNECTION_TEST_HPP

#include <gtest/gtest.h>
#include "telnet_connection.hpp"

class OverridedTelnetConnection : public TelnetConnection
{
public:
    OverridedTelnetConnection()
    : TelnetConnection(0, nullptr, nullptr)
    {
    }

    bool ExtractCommand(const string & message, string & command)
    {
        return TelnetConnection::ExtractCommand(message, command);
    }
};


class TelnetConnectionTest : public testing::Test
{
protected:
    OverridedTelnetConnection * _sut;
public:
    void SetUp() override
    {
        this->_sut = new OverridedTelnetConnection();
    }

    void TearDown() override
    {
        delete this->_sut;
    }
};

TEST_F(TelnetConnectionTest, ExtractNoCommand)
{
    string message = "", command = "";

    EXPECT_FALSE(_sut->ExtractCommand(message, command));
}

TEST_F(TelnetConnectionTest, CommandWithSpace)
{
    string message = "command parameter", command = "";

    EXPECT_TRUE(_sut->ExtractCommand(message, command));
    EXPECT_STREQ(string("command").c_str(), command.c_str());
}

TEST_F(TelnetConnectionTest, CommandWithEnter)
{
    string message = "command\rparameter", command = "";

    EXPECT_TRUE(_sut->ExtractCommand(message, command));
    EXPECT_STREQ(string("command").c_str(), command.c_str());
}

#endif
