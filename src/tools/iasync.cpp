#include "iasync.hpp"
#include "logger.hpp"
#include <thread>

using namespace std;

namespace tools
{

int IAsync::_idGenerator = 0;
map <int, IAsync *> IAsync::_activeJobs;

void IAsync::StopActiveJobs()
{
    Logger::Log("IAsync: stopping active workers");

    auto maxDelay = IAsync::DelayMS(0);

    for (auto & pair : IAsync::_activeJobs)
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

void IAsync::Register()
{
    this->_id = IAsync::_idGenerator++;
    IAsync::_activeJobs[this->_id] = this;
}

void IAsync::Deregister()
{
    auto item = IAsync::_activeJobs.find(this->_id);
    IAsync::_activeJobs.erase(item);
}

} // namespace tools
