#include <string>
#include <map>

class SignalHandler
{
    SignalHandler() = delete;
    ~SignalHandler() = delete;

    static std::map<int, std::string> _signalNames;

    static void Handler(int signal_number);
public:
    static void RegisterExitSignals();
};
