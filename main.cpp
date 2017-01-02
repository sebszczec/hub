#include <iostream>
#include "hub.hpp"

int main()
{
    Hub hub;
    if (hub.Start())
    {
        std::cout << "Hub started" << std::endl;
        return 0;
    }

    std::cout << "Hub can't be started" << std::endl;
}

