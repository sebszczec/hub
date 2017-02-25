#ifndef __DELEGATE_HPP
#define __DELEGATE_HPP

#include <functional>
#include <vector>

using namespace std;

class Delegate
{
private:
    vector<function<void()>> _methods;
public:
    Delegate() = default;
    ~Delegate() = default;

    template <class Function, class... ARGS>
    void AddMethod(Function&& function, ARGS&&... args)
    {
        this->_methods.push_back(bind(function, args...));
    }

    void Run()
    {
        for (auto & item : this->_methods)
        {
            item();
        }
    }
};

#endif
