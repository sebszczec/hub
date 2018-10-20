#ifndef __STRINGS_HPP
#define __STRINGS_HPP

#include <string>

namespace machine 
{
    namespace string
    {
        static const std::string sigint = "SIGINT";
        static const std::string sigabrt = "SIGABRT";
        static const std::string sigterm = "SIGTERM";

        static const std::string timeFormat = "%Y-%m-%d %X";

        static const std::string dbg = "DBG";
        static const std::string err = "ERR";
        static const std::string inf = "INF";
        static const std::string endl = "\n";

        static const std::string daemonMessage1 = "Daemon: starting initialization";
        static const std::string daemonMessage2 = "Daemon: going background";
        static const std::string daemonMessage3 = "Daemon: getting new PID FAILED";
        static const std::string daemonMessage4 = "Daemon: getting new SID FAILED";
        static const std::string daemonMessage5 = "Daemon: changing root path FAILED";
        static const std::string daemonMessage6 = "Daemon: changing root path SUCCESSED";
        static const std::string daemonMessage7 = "Daemon: disabling standard descriptors SUCCESSED";
        static const std::string daemonMessage8 = "Daemon: staying in foreground";

        static const std::string telnet = "Telnet";
        static const std::string telnetWelcomeMessage = "Welcome\n";
        static const std::string mobile = "Mobile";

        static const std::string settingsFileName = "";

    } // string

} // machine

#endif
