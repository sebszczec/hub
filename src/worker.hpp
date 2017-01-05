#include <thread>
#include <unistd.h>
#include <exception>
#include <iostream>
#include <map>

using namespace std;

class Worker
{
public:
    using DelayMS = std::chrono::duration<int, std::milli>;

private:
    static int _idGenerator;
    static map <int, Worker *> _activeWorkes;

    int _id = 0;
    bool _isLooped = false;
    DelayMS _delay = DelayMS(0); // miliseconds
    bool _stop = false;

    void Register();
    void Deregister();

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
               if (this->_stop)
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
    static void StopActiveJobs();

    Worker() = default;

    Worker(bool isLooped, DelayMS delay)
    : _isLooped(isLooped), _delay(delay)
    {
        this->Register();
    }

    Worker(bool isLooped)
    : Worker(isLooped, DelayMS(0))
    {}

    ~Worker()
    {
        this->Deregister();
    };

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