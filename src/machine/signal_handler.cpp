#include <csignal>
#include "signal_handler.hpp"
#include "system.hpp"
#include "strings.hpp"

namespace machine
{

std::map<int, std::string> SignalHandler::_signalNames;

void SignalHandler::Handler(int signal_number)
{
    System::GetLogger()->LogError("Signal " + SignalHandler::_signalNames[signal_number] + " received, cleanning resources and quiting..");
    System::Stop();
    exit(EXIT_FAILURE);
}

void SignalHandler::RegisterExitSignals()
{
    auto logger = System::GetLogger();

    SignalHandler::_signalNames[SIGINT] = machine::string::sigint;
    SignalHandler::_signalNames[SIGABRT] = machine::string::sigabrt;
    SignalHandler::_signalNames[SIGTERM] = machine::string::sigterm;

    for (const auto &pair : SignalHandler::_signalNames)
    {
        logger->LogDebug("Registering " + pair.second + " signal");
        signal(pair.first, SignalHandler::Handler);
    }

    signal(SIGPIPE, SIG_IGN);
}

} // namespace machine
