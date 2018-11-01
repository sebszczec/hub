#include <gtest/gtest.h>
#include "logger.hpp"
#include "signal_handler.hpp"
#include "access_level_test.hpp"
#include "account_manager_test.hpp"
#include "command_manager_test.hpp"
#include "configuration_manager_test.hpp"
#include "context_manager_test.hpp"
#include "database_test.hpp"
#include "delegate_test.hpp"
#include "help_command_test.hpp"
#include "login_command_test.hpp"
#include "logout_command_test.hpp"
#include "ls_command_test.hpp"
#include "memory_manager_test.hpp"
#include "system_test.hpp"
#include "tcp_base_test.hpp"
#include "telnet_connection_test.hpp"
#include "timer_test.hpp"
#include "uptime_command_test.hpp"
#include "user_test.hpp"
#include "whoami_command_test.hpp"
#include "worker_test.hpp"

using machine::Logger;

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);

  machine::System::InitializeMembersForUT();
  machine::SignalHandler::RegisterExitSignals();
  auto result = RUN_ALL_TESTS();
  machine::System::FreeMembersForUT();

  return result;
}
