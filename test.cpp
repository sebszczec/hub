#include <gtest/gtest.h>
#include "system_test.hpp"
#include "uptime_command_test.hpp"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
