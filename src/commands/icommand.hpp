#ifndef __I_COMMAND
#define __I_COMMAND

#include <string>
#include <vector>

using namespace std;

class CommandArgument
{
public:
    CommandArgument() = default;
    ~CommandArgument() = default;

    vector<string> Args;
};

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual string Register() = 0;
    virtual string PrintHelp() = 0;
    virtual bool Execute(const CommandArgument &) = 0;
    virtual string GetResult() = 0;
};

#endif
