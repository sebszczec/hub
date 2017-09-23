#ifndef __DELEGATE_HPP
#define __DELEGATE_HPP

#include <functional>
#include <vector>
#include <iostream>

using namespace std;

class DelegateArgument
{
public:
    void * Sender;
    vector<void *> Arguments;
};

using namespace std::placeholders;

class Delegate
{
private:
    vector<function<void(DelegateArgument &)>> _methods;
public:
    Delegate() = default;
    ~Delegate() = default;

    template <class Function, class... ARGS>
    void AddMethod(Function&& function, DelegateArgument & argument, ARGS&&... args)
    {
        this->_methods.push_back(bind(function, _1, args...));
    }

    void Run(DelegateArgument & argument)
    {
        for (auto & item : this->_methods)
        {
            item(argument);
        }
    }

    void Clear()
    {
        this->_methods.clear();
    }
};

#endif
