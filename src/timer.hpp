#include <thread>
#include <unistd.h>
#include <exception>
#include <iostream>
#include <map>
#include "iasync.hpp"

using namespace std;

class Timer : public IAsync
{
private:

    template <class Function, class... ARGS>
    void StartThread(Function&& function, ARGS&&... args)
    {
       auto binded = std::bind(function, args...);
       std::thread t([=](){
           this_thread::sleep_for(this->_delay);
           binded();
       });
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
               this_thread::sleep_for(this->_delay);
               binded();
           }
       });
       t.detach();
    }

public:

    Timer() = delete;

    Timer(DelayMS delay, bool isLooped)
    : IAsync(isLooped, delay)
    {
    }

    Timer(DelayMS delay)
    : Timer(delay, false)
    {}

    ~Timer() = default;

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