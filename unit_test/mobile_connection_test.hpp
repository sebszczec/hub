#ifndef __MOBILE_CONNECTION_TEST_HPP
#define __MOBILE_CONNECTION_TEST_HPP

#include <gtest/gtest.h>
#include "mobile_connection.hpp"
#include "system.hpp"

using namespace network;

class MobileConnectionTest : public testing::Test
{
protected:
    MobileConnection * _sut;
public:
    void SetUp() override
    {
        this->_sut = new MobileConnection(0, nullptr, nullptr);
    }

    void TearDown() override
    {
        delete this->_sut;
    }
};

#endif
