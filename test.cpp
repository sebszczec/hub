#include <gtest/gtest.h>
#include "connection_manager_test.hpp"
#include "context_manager_test.hpp"
#include "delegate_test.hpp"
#include "memory_manager_test.hpp"
#include "system_test.hpp"
#include "telnet_connection_test.hpp"
#include "uptime_command_test.hpp"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
