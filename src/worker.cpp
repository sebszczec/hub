#include "worker.hpp"
#include "logger.hpp"

using namespace std;

int Worker::_idGenerator = 0;
map <int, Worker *> Worker::_activeWorkes;

void Worker::StopActiveJobs()
{
    Logger::LogDebug("Worker: stopping active workers");

    auto maxDelay = Worker::DelayMS(0);

    for (auto & pair : Worker::_activeWorkes)
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

void Worker::Register()
{
    this->_id = Worker::_idGenerator++;
    Worker::_activeWorkes[this->_id] = this;
}

void Worker::Deregister()
{
    auto item = Worker::_activeWorkes.find(this->_id);
    Worker::_activeWorkes.erase(item);
}

