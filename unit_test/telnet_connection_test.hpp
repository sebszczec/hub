#ifndef __TELNET_CONNECTION_TEST_HPP
#define __TELNET_CONNECTION_TEST_HPP

#include <gtest/gtest.h>
#include "telnet_connection.hpp"
#include "tcp_base.hpp"
#include "system.hpp"
#include "icommand.hpp"
#include "strings.hpp"

using namespace commands;
using namespace network;

class TelnetConnectionTest : public testing::Test
{
protected:
    boost::asio::io_service _ios;
    boost::asio::ssl::context _context;
    TcpBase _parent;
    TelnetConnection * _sut;
public:
    TelnetConnectionTest()
    : _ios(),
    _context(boost::asio::ssl::context::sslv23),
    _parent(machine::string::telnet, false)
    {}

    void SetUp() override
    {
        this->_sut = new TelnetConnection(_ios, _parent, _context);
    }

    void TearDown() override
    {
        delete this->_sut;
    }
};

TEST_F(TelnetConnectionTest, GetContext)
{
    auto context = _sut->GetContext();
    EXPECT_NE((unsigned int)-1, context.GetId());
}

TEST_F(TelnetConnectionTest, GetSocket)
{
    auto & context = _sut->GetSocket();
    (void)context;
}

TEST_F(TelnetConnectionTest, ExtractNoCommand)
{
    string message = "", command = "";
    CommandArgument arg;

    EXPECT_FALSE(_sut->ExtractCommand(message, command, arg));
}

TEST_F(TelnetConnectionTest, CommandWithSpace)
{
    string message = "command parameter", command = "";
    CommandArgument arg;

    EXPECT_TRUE(_sut->ExtractCommand(message, command, arg));
    EXPECT_STREQ(string("command").c_str(), command.c_str());
}

TEST_F(TelnetConnectionTest, CommandWithEnter)
{
    string message = "command\rparameter", command = "";
    CommandArgument arg;

    EXPECT_TRUE(_sut->ExtractCommand(message, command, arg));
    EXPECT_STREQ(string("command").c_str(), command.c_str());
}

TEST_F(TelnetConnectionTest, EmptyParameters)
{
    string message = "";
    CommandArgument arg;

    _sut->ExtractParameters(message, arg);

    EXPECT_EQ(0, arg.Args.size());
}

TEST_F(TelnetConnectionTest, ExtractParameters)
{
    string message = "parameter1 parameter2 parameter3\r";
    CommandArgument arg;

    _sut->ExtractParameters(message, arg);

    ASSERT_EQ(3, arg.Args.size());
    EXPECT_STREQ(string("parameter1").c_str(), arg.Args[0].c_str());
    EXPECT_STREQ(string("parameter2").c_str(), arg.Args[1].c_str());
    EXPECT_STREQ(string("parameter3").c_str(), arg.Args[2].c_str());
}

TEST_F(TelnetConnectionTest, ExtractParametersWithoutEnter)
{
    string message = "parameter1 parameter2 parameter3";
    CommandArgument arg;

    _sut->ExtractParameters(message, arg);

    ASSERT_EQ(2, arg.Args.size());
    EXPECT_STREQ(string("parameter1").c_str(), arg.Args[0].c_str());
    EXPECT_STREQ(string("parameter2").c_str(), arg.Args[1].c_str());
}

TEST_F(TelnetConnectionTest, CommandWithParameters)
{
    string message = "command parameter1 parameter2\r", command = "";
    CommandArgument arg;

    EXPECT_TRUE(_sut->ExtractCommand(message, command, arg));
    EXPECT_STREQ(string("command").c_str(), command.c_str());

    ASSERT_EQ(2, arg.Args.size());
    EXPECT_STREQ(string("parameter1").c_str(), arg.Args[0].c_str());
    EXPECT_STREQ(string("parameter2").c_str(), arg.Args[1].c_str());
}

TEST_F(TelnetConnectionTest, CommandWithCarriageReturn)
{
    // 0xd - carriage
    char hexTable1[] = { 0x2e, 0x6c, 0x73, 0xd, 0xa };
    string message(hexTable1);
    string command = "";
    CommandArgument arg;

    EXPECT_TRUE(_sut->ExtractCommand(message, command, arg));
    EXPECT_STREQ(string(".ls").c_str(), command.c_str());
}

// issue found when SSL enabled -> no carriage but only new line is present
TEST_F(TelnetConnectionTest, CommandWithoutCarriageReturn)
{
    // 0xd - carriage
    char hexTable1[] = { 0x2e, 0x6c, 0x73, 0xa };
    string message(hexTable1);
    string command = "";
    CommandArgument arg;

    EXPECT_TRUE(_sut->ExtractCommand(message, command, arg));
    EXPECT_STREQ(string(".ls").c_str(), command.c_str());
}

TEST_F(TelnetConnectionTest, ParamenterWithCarriageReturn)
{
    // 0xd - carriage
    char hexTable1[] = { 0x2e, 0x6c, 0x73, 0xd, 0xa };
    string message(hexTable1);
    string command = "";
    CommandArgument arg;

    _sut->ExtractParameters(message, arg);
    ASSERT_EQ(1, arg.Args.size());
    EXPECT_STREQ(string(".ls").c_str(), arg.Args[0].c_str());
}

// issue found when SSL enabled -> no carriage but only new line is present
TEST_F(TelnetConnectionTest, ParameterWithoutCarriageReturn)
{
    // 0xd - carriage
    char hexTable1[] = { 0x2e, 0x6c, 0x73, 0xa };
    string message(hexTable1);
    string command = "";
    CommandArgument arg;

    _sut->ExtractParameters(message, arg);
    ASSERT_EQ(1, arg.Args.size());
    EXPECT_STREQ(string(".ls").c_str(), arg.Args[0].c_str());
}

#endif
