#include <string>
#include <fstream>

class Logger
{
    static std::string _filename;
    static int _flushResolution;
    static int _flushCounter;
    static std::fstream _file;
    static std::string _buffer;

    Logger() = delete;
    ~Logger() = delete;

    static void Flush();
public:
    static void Initilize(const std::string &filename, int flushResolution);

    static void LogDebug(const std::string &text);
    static void LogError(const std::string &text);
    static void Log(const std::string &text);
};
