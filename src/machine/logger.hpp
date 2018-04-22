#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

namespace machine
{

enum LogLevel
{
    Debug,
    Info,
    Error
};

class Logger
{
    std::string _filename;
    int _flushResolution;
    int _flushCounter;
    std::fstream _file;
    std::string _buffer;
    LogLevel _logLevel;
    
    std::mutex _mutex; // mutex needed when flushing logs

    void Flush(bool force = false);
    void Log(const std::string &prefix, const std::string &text);
    std::string CurrentTime();
public:
    Logger();
    ~Logger() = default;

    void Initilize(const std::string &filename, int flushResolution);
    void Initilize(const std::string &filename, int flushResolution, LogLevel logLevel);
    
    void ClearResources();

    void LogDebug(const std::string &text);
    void LogError(const std::string &text);
    void Log(const std::string &text);
    LogLevel GetLogLevel() { return this->_logLevel; }
    void SetLogLevel (LogLevel value ) { this->_logLevel = value; }
};

}  // namespace machine

#endif

