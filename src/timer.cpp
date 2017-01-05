#include "timer.hpp"
#include "logger.hpp"

using namespace std;

int Timer::_idGenerator = 0;
map <int, Timer *> Timer::_activeWorkes;

void Timer::StopActiveJobs()
{
    Logger::LogDebug("Timer: stopping active timers");

    auto maxDelay = Timer::DelayMS(0);

    for (auto & pair : Timer::_activeWorkes)
    {
        auto & element = pair.second;
        if(!element->_isLooped)
        {
            continue;
        }

        element->Stop();
        if (element->_delay > maxDelay)
        {
            maxDelay = element->_delay;
        }
    }

    this_thread::sleep_for(maxDelay);
}

void Timer::Register()
{
    this->_id = Timer::_idGenerator++;
    Timer::_activeWorkes[this->_id] = this;
}

void Timer::Deregister()
{
    auto item = Timer::_activeWorkes.find(this->_id);
    Timer::_activeWorkes.erase(item);
}
