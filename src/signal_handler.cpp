#include <csignal>
#include "signal_handler.hpp"
#include "logger.hpp"
#include "configuration_manager.hpp"

std::map<int, std::string> SignalHandler::_signalNames;

void SignalHandler::Handler(int signal_number)
{
    Logger::LogError("Signal " + SignalHandler::_signalNames[signal_number] + " received, cleanning resources and quiting..");
    ConfigurationManager::CleanResources();
    Logger::CleanResources();
    exit(EXIT_FAILURE);
}

void SignalHandler::RegisterExitSignals()
{
    SignalHandler::_signalNames[SIGINT] = "SIGINT";
    SignalHandler::_signalNames[SIGABRT] = "SIGABRT";
    SignalHandler::_signalNames[SIGTERM] = "SIGTERM";

    for (const auto &pair : SignalHandler::_signalNames)
    {
        Logger::LogDebug("Registering " + pair.second + " signal");
        signal(pair.first, SignalHandler::Handler);
    }
}