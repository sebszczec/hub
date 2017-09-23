#ifndef __SYSTEM_TEST_HPP
#define __SYSTEM_TEST_HPP

#include <gtest/gtest.h>
#include "system.hpp"

TEST(SystemTest, UpTime)
{
    auto zero = machine::System::DelayUS(0);
    auto uptime = machine::System::UpTime();

    EXPECT_TRUE(uptime > zero);
}

#endif
