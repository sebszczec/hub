#include "daemon.hpp"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include "logger.hpp"
#include <fstream>
#include "configuration_manager.hpp"

void Daemon::Initilize(bool goBackground)
{
    Logger::Log("Daemon: starting initialization");

    if (goBackground)
    {
        Logger::Log("Daemon: going background");

        /* Fork off the parent process */
        this->_pid = fork();
        if (this->_pid < 0) 
        {
                Logger::LogError("Daemon: getting new PID FAILED");
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
                we can exit the parent process. */
        if (this->_pid > 0) 
        {
                Logger::Log("Daemon: getting new PID SUCCESSED, value: " + std::to_string(this->_pid) + ", parrent exiting");
                SavePidToFile();
                exit(EXIT_SUCCESS);
        }
        
        /* Change the file mode mask */
        umask(0);
                
        /* Open any logs here */        
                
        /* Create a new SID for the child process */
        this->_sid = setsid();
        if (this->_sid < 0) 
        {
                /* Log the failure */
                Logger::LogError("Daemon: getting new SID FAILED");
                exit(EXIT_FAILURE);
        }
        Logger::Log("Daemon: getting new SID SUCCESSED, value: " + std::to_string(this->_sid));

        /* Change the current working directory */
        if ((chdir("/")) < 0) 
        {
                /* Log the failure */
                Logger::LogError("Daemon: changing root path FAILED");
                exit(EXIT_FAILURE);
        }
        Logger::Log("Daemon: changing root path SUCCESSED");

        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        Logger::Log("Daemon: disabling standard descriptors SUCCESSED");

        /* Daemon-specific initialization goes here */

        return;
    }

    Logger::Log("Daemon: staying in foreground");
    this->_pid = getpid();
    Logger::Log("Daemon: PID value: " + std::to_string(this->_pid));
    Daemon::SavePidToFile();

}

void Daemon::SavePidToFile()
{
    using namespace std;
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    auto name = CM::GetResource(CMV::PidFileName).ToString();
    fstream file;
    file.open(name, fstream::out | fstream::trunc);
    file << to_string(this->_pid) << endl;
    file.close();

    Logger::LogDebug("Daemon: PID saved to " + name);
}