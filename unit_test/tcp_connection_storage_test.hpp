#ifndef __TCP_CONNECTION_STORAGE_TEST_HPP
#define __TCP_CONNECTION_STORAGE_TEST_HPP

#include <gtest/gtest.h>
#include "tcp_connection_storage.hpp"
#include "telnet_connection.hpp"
#include "strings.hpp"

using namespace commands;
using namespace network;

class TcpConnectionStorageTest : public testing::Test
{
protected:
    TcpConnectionStorage * _sut;
public:

    void SetUp() override
    {
        this->_sut = new TcpConnectionStorage(machine::string::telnet);
    }

    void TearDown() override
    {
        delete this->_sut;
    }
};

TEST_F(TcpConnectionStorageTest, NoConnectionsAtStart)
{
    EXPECT_EQ(0, _sut->GetConnections().size());
}   

TEST_F(TcpConnectionStorageTest, AddConnection)
{
    EXPECT_EQ(0, _sut->GetConnections().size());

    boost::asio::io_service ios;
    EXPECT_EQ(0, _sut->GetConnections().size());

    auto pointer = std::make_shared<TelnetConnection>(ios, *_sut);
    
    _sut->AddConnection(pointer);
    EXPECT_EQ(1, _sut->GetConnections().size());
}  

TEST_F(TcpConnectionStorageTest, RemoveConnection)
{
    boost::asio::io_service ios;
    auto pointer = std::make_shared<TelnetConnection>(ios, *_sut);
    
    _sut->AddConnection(pointer);
    EXPECT_EQ(1, _sut->GetConnections().size());

    _sut->RemoveConnection(pointer);
    EXPECT_EQ(0, _sut->GetConnections().size());
} 

#endif // __TCP_CONNECTION_STORAGE_TEST_HPP
