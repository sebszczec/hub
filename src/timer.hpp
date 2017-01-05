#include <thread>
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace std;

class Timer
{
public:
    using DelayMS = std::chrono::duration<int, std::milli>;

private:
    bool _isLooped = false;
    DelayMS _delay = DelayMS(0); // miliseconds
    bool _stop = false;

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
               if (this->_stop)
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

    Timer(DelayMS delay)
    : _delay(delay)
    {}

    Timer(DelayMS delay, bool isLooped)
    : _delay(delay), _isLooped(isLooped)
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

    void SetLooping(bool isLooped)
    {
        this->_isLooped = isLooped;
    }

    void SetDelay(DelayMS delay)
    {
        this->_delay = delay;
    }

    void Stop()
    {
        this->_stop = true;
    }
};