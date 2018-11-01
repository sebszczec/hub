#ifndef __TCP_CONNECTION_STORAGE_TEST_HPP
#define __TCP_CONNECTION_STORAGE_TEST_HPP

#include <gtest/gtest.h>
#include "tcp_base.hpp"
#include "telnet_connection.hpp"
#include "strings.hpp"

using namespace commands;
using namespace network;

class TcpBaseTest : public testing::Test
{
protected:
    TcpBase * _sut;
public:

    void SetUp() override
    {
        this->_sut = new TcpBase(machine::string::telnet);
    }

    void TearDown() override
    {
        delete this->_sut;
    }
};

TEST_F(TcpBaseTest, NoConnectionsAtStart)
{
    EXPECT_EQ(0, _sut->GetConnections().size());
}   

TEST_F(TcpBaseTest, AddConnection)
{
    EXPECT_EQ(0, _sut->GetConnections().size());

    boost::asio::io_service ios;
    EXPECT_EQ(0, _sut->GetConnections().size());

    auto pointer = std::make_shared<TelnetConnection>(ios, *_sut);
    
    _sut->AddConnection(pointer);
    EXPECT_EQ(1, _sut->GetConnections().size());
}  

TEST_F(TcpBaseTest, RemoveConnection)
{
    boost::asio::io_service ios;
    auto pointer = std::make_shared<TelnetConnection>(ios, *_sut);
    
    _sut->AddConnection(pointer);
    EXPECT_EQ(1, _sut->GetConnections().size());

    _sut->RemoveConnection(pointer);
    EXPECT_EQ(0, _sut->GetConnections().size());
} 

#endif // __TCP_CONNECTION_STORAGE_TEST_HPP
