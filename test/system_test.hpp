#ifndef __SYSTEM_TEST_HPP
#define __SYSTEM_TEST_HPP

#include <gtest/gtest.h>
#include "system.hpp"

TEST(SystemTest, UpTime)
{
    auto zero = System::DelayUS(0);
    auto uptime = System::UpTime();

    EXPECT_TRUE(uptime > zero);
}

#endif
