#ifndef __I_ASYNC
#define __I_ASYNC

#include <chrono>
#include <map>

using namespace std;

namespace tools
{

class IAsync
{
public:
    using DelayMS = std::chrono::duration<int, std::milli>;

    static void StopActiveJobs();

protected:
    static int _idGenerator;
    static map <int, IAsync *> _activeJobs;

    int _id = 0;
    bool _isLooped = false;
    DelayMS _delay = DelayMS(0); // miliseconds

    void Register();
    void Deregister();

public:
    IAsync() = default;

    IAsync(bool isLooped, DelayMS delay)
    : _isLooped(isLooped), _delay(delay)
    {
        this->Register();
    }

    IAsync(bool isLooped)
    : IAsync(isLooped, DelayMS(0))
    {}

    ~IAsync()
    {
        this->Deregister();
    };

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
        this->_isLooped = false;
    }
};

} // namespace tools


#endif // __I_ASYNC
