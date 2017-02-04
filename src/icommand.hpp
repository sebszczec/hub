#ifndef __I_COMMAND
#define __I_COMMAND

#include <string>

using namespace std;

class ICommand
{
public:
    virtual string Register() = 0;
    virtual string PrintHelp() = 0;
    virtual bool Execute() = 0;
    virtual string GetResult() = 0;
};

#endif
