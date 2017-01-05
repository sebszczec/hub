#include "worker.hpp"
#include "logger.hpp"

using namespace std;

int Worker::_idGenerator = 0;
map <int, Worker *> Worker::_activeWorkes;

void Worker::StopActiveJobs()
{
    Logger::LogDebug("Stopping active workers");
    for (auto & pair : Worker::_activeWorkes)
    {
        pair.second->Stop();
    }

    this_thread::sleep_for(DelayMS(2000));
}

