#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

class Daemon
{
    pid_t _pid = 0;
    pid_t _sid = 0;

public:
    Daemon() = default;
    void Initilize()
    {
        /* Fork off the parent process */
        this->_pid = fork();
        if (this->_pid < 0) 
        {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
            we can exit the parent process. */
        if (this->_pid > 0) 
        {
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
                exit(EXIT_FAILURE);
        }
        
        /* Change the current working directory */
        if ((chdir("/")) < 0) 
        {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }
        
        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        /* Daemon-specific initialization goes here */
    }
};

int main()
{
    Daemon daemon;
    daemon.Initilize();
    
    /* The Big Loop */
    while (1) 
    {
        /* Do some task here ... */    
        sleep(30); /* wait 30 seconds */
    }

   exit(EXIT_SUCCESS);
}

