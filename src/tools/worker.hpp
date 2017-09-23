#include <thread>
#include <unistd.h>
#include <exception>
#include <iostream>
#include <map>
#include "iasync.hpp"

using namespace std;

namespace tools 
{

class Worker : public IAsync
{

private:
    template <class Function, class... ARGS>
    void StartThread(Function&& function, ARGS&&... args)
    {
       auto binded = std::bind(function, args...);
       std::thread t(binded);
       t.detach();
    }

    template <class Function, class... ARGS>
    void StartThreadLooped(Function&& function, ARGS&&... args)
    {
       auto binded = std::bind(function, args...);
       std::thread t([=](){
           while (true)
           {
               if (!this->_isLooped)
               {
                   return;
               }
               binded();
               this_thread::sleep_for(this->_delay);
           }
       });
       t.detach();
    }

public:
    Worker() = default;

    Worker(bool isLooped, DelayMS delay)
    : IAsync(isLooped, delay)
    {
    }

    Worker(bool isLooped)
    : Worker(isLooped, DelayMS(0))
    {}

    ~Worker() = default;

    template <class Function, class... ARGS>
    void StartAsync(Function&& function, ARGS&&... args)
    {
        if (!this->_isLooped)
        {
            this->StartThread(function, args...);
            return;
        }

        this->StartThreadLooped(function, args...);
    }
};

} // namespace tools

