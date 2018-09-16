#include "daemon.hpp"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <fstream>
#include "system.hpp"
#include "strings.hpp"

namespace machine
{

pid_t Daemon::_pid = 0;
pid_t Daemon::_sid = 0;

void Daemon::Initilize(bool goBackground)
{
        auto logger = System::GetLogger();

        logger->Log(machine::string::daemonMessage1);

        if (goBackground)
        {
                logger->Log(machine::string::daemonMessage2);

                /* Fork off the parent process */
                Daemon::_pid = fork();
                if (Daemon::_pid < 0) 
                {
                        logger->LogError(machine::string::daemonMessage3);
                        exit(EXIT_FAILURE);
                }
                /* If we got a good PID, then
                        we can exit the parent process. */
                if (Daemon::_pid > 0) 
                {
                        logger->Log("Daemon: getting new PID SUCCESSED, value: " + std::to_string(Daemon::_pid) + ", parrent exiting");
                        SavePidToFile();
                        exit(EXIT_SUCCESS);
                }

                /* Change the file mode mask */
                umask(0);
                        
                /* Open any logs here */        
                        
                /* Create a new SID for the child process */
                Daemon::_sid = setsid();
                if (Daemon::_sid < 0) 
                {
                        /* Log the failure */
                        logger->LogError(machine::string::daemonMessage4);
                        exit(EXIT_FAILURE);
                }
                logger->Log("Daemon: getting new SID SUCCESSED, value: " + std::to_string(Daemon::_sid));

                /* Change the current working directory */
                if ((chdir("/")) < 0) 
                {
                        /* Log the failure */
                        logger->LogError(machine::string::daemonMessage5);
                        exit(EXIT_FAILURE);
                }
                logger->Log(machine::string::daemonMessage6);

                /* Close out the standard file descriptors */
                close(STDIN_FILENO);
                close(STDOUT_FILENO);
                close(STDERR_FILENO);
                logger->Log(machine::string::daemonMessage7);

                /* Daemon-specific initialization goes here */

                return;
        }

        logger->Log(machine::string::daemonMessage8);
        Daemon::_pid = getpid();
        logger->Log("Daemon: PID value: " + std::to_string(Daemon::_pid));
        Daemon::SavePidToFile();

}

void Daemon::SavePidToFile()
{
    using namespace std;
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    auto name = System::GetConfigurationManager()->GetResource(CMV::PidFileName).ToString();
    fstream file;
    file.open(name, fstream::out | fstream::trunc);
    file << to_string(Daemon::_pid) << endl;
    file.close();

    System::GetLogger()->LogDebug("Daemon: PID saved to " + name);
}

} // namespace machine
