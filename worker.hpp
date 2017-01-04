#include <thread>

class Worker
{
public:
    Worker() = default;
    ~Worker() = default;

    template <class Function, class... ARGS>
    void StartAsync(Function&& f, ARGS&&... args)
    {
       auto _f = std::bind(f, args...);
       std::thread t(_f);

       t.join();
    }
};