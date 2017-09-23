#ifndef __CONNECTION_MANAGER_TEST_HPP
#define __CONNECTION_MANAGER_TEST_HPP

#include <gtest/gtest.h>
#include "connection_manager.hpp"
#include "telnet_connection.hpp"

using namespace network;

class ConnectionManagerTest : public testing::Test 
{
protected:
    ConnectionManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new ConnectionManager();
    }

    void TearDown() override
    {
        if (_sut != nullptr)
        {
            delete _sut;
            _sut = nullptr;
        }
    }
};

TEST_F(ConnectionManagerTest, GetConnectionNotExisting)
{
    int sockFd = 1;
    ASSERT_THROW(_sut->GetConnection(sockFd), ConnectionNotFoundException);
    EXPECT_EQ(0, _sut->GetNumberOfConnections());
}

TEST_F(ConnectionManagerTest, GetConnection)
{
    int sockFd = -1;
    inet_stream * stream = new inet_stream();   
    _sut->AddConnection<TelnetConnection>(*stream);

    EXPECT_NO_THROW(_sut->GetConnection(sockFd));
    EXPECT_EQ(1, _sut->GetNumberOfConnections());

    _sut->RemoveConnection(sockFd);
    EXPECT_EQ(0, _sut->GetNumberOfConnections());
}

#endif
