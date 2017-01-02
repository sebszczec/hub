#include "daemon.hpp"
#include <stdlib.h>
#include <unistd.h>

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

