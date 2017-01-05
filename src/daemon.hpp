#include <sys/types.h>

class Daemon
{
    pid_t _pid = 0;
    pid_t _sid = 0;

    void SavePidToFile();
public:
    Daemon() = default;
    ~Daemon() = default;
    
    pid_t GetPid() 
    {
        return this->_pid;
    }

    pid_t GetSid() 
    {
        return this->_sid;
    }

    void Initilize(bool goBackground);
};