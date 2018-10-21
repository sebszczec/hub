#ifndef __WORKER_TEST_HPP
#define __WORKER_TEST_HPP

#include <gtest/gtest.h>
#include <iostream>
#include "worker.hpp"

class WorkerTest : public testing::Test
{
public:

};

TEST_F(WorkerTest, RunInBackground)
{
    tools::Worker worker(false);
    worker.StartAsync([]() {});

    EXPECT_TRUE(true);
}

TEST_F(WorkerTest, RunInBackgroundLooped)
{
    tools::Worker worker(true);
    worker.StartAsync([]() {});

    worker.Stop();

    EXPECT_TRUE(true);
}

TEST_F(WorkerTest, RunInBackgroundMany)
{
    tools::Worker worker1(true);
    worker1.StartAsync([]() {});

    tools::Worker worker2(true);
    worker2.StartAsync([]() {});

    tools::IAsync::StopActiveJobs();

    EXPECT_TRUE(true);
}

#endif // __WORKER_TEST_HPP
