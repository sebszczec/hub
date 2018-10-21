#ifndef __TIMER_TEST_HPP
#define __TIMER_TEST_HPP

#include <gtest/gtest.h>
#include <iostream>
#include "timer.hpp"

class TimerTest : public testing::Test
{
public:

};

TEST_F(TimerTest, RunInBackground)
{
    auto delay = tools::IAsync::DelayMS(1);

    tools::Timer timer(delay);
    timer.StartAsync([]() {});

    EXPECT_TRUE(true);
}

TEST_F(TimerTest, RunInBackgroundLooped)
{
    auto delay = tools::IAsync::DelayMS(1);

    tools::Timer timer(delay, true);
    timer.StartAsync([]() {});

    timer.Stop();

    EXPECT_TRUE(true);
}

TEST_F(TimerTest, DISABLED_RunInBackgroundMany)
{
    auto delay = tools::IAsync::DelayMS(1);

    tools::Timer timer1(delay, true);
    timer1.StartAsync([]() {});

    tools::Timer timer2(delay, true);
    timer2.StartAsync([]() {});

    tools::IAsync::StopActiveJobs();

    EXPECT_TRUE(true);
}

#endif // __TIMER_TEST_HPP
