#ifndef __DAEMON_HPP
#define __DAEMON_HPP

#include <sys/types.h>

namespace machine
{

class Daemon
{
    static pid_t _pid;
    static pid_t _sid;

    static void SavePidToFile();
public:
    Daemon() = delete;
    ~Daemon() = delete;
    
    static pid_t GetPid() 
    {
        return Daemon::_pid;
    }

    static pid_t GetSid() 
    {
        return Daemon::_sid;
    }

    static void Initilize(bool goBackground);
};

} // namespace machine

#endif
