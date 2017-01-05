#include "worker.hpp"
#include "logger.hpp"

using namespace std;

int Worker::_idGenerator = 0;
map <int, Worker *> Worker::_activeWorkes;

void Worker::StopActiveJobs()
{
    Logger::LogDebug("Stopping active workers");

    auto maxDelay = Worker::DelayMS(0);

    for (auto & pair : Worker::_activeWorkes)
    {
        pair.second->Stop();
        if (pair.second->_delay > maxDelay)
        {
            maxDelay = pair.second->_delay;
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

