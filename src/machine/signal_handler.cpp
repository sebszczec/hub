#include <csignal>
#include "signal_handler.hpp"
#include "system.hpp"

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

    SignalHandler::_signalNames[SIGINT] = "SIGINT";
    SignalHandler::_signalNames[SIGABRT] = "SIGABRT";
    SignalHandler::_signalNames[SIGTERM] = "SIGTERM";

    for (const auto &pair : SignalHandler::_signalNames)
    {
        logger->LogDebug("Registering " + pair.second + " signal");
        signal(pair.first, SignalHandler::Handler);
    }
}

} // namespace machine
