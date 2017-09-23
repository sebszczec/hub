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
    static std::string _filename;
    static int _flushResolution;
    static int _flushCounter;
    static std::fstream _file;
    static std::string _buffer;
    static LogLevel _logLevel;
    
    static std::mutex _mutex; // mutex needed when flushing logs

    Logger() = delete;
    ~Logger() = delete;

    static void Flush(bool force = false);
    static void Log(const std::string &prefix, const std::string &text);
    static std::string CurrentTime();
public:
    static void Initilize(const std::string &filename, int flushResolution);
    static void Initilize(const std::string &filename, int flushResolution, LogLevel logLevel);
    
    static void ClearResources();

    static void LogDebug(const std::string &text);
    static void LogError(const std::string &text);
    static void Log(const std::string &text);
    static LogLevel GetLogLevel() { return Logger::_logLevel; }
    static void SetLogLevel (LogLevel value ) { Logger::_logLevel = value; }
};

}  // namespace machine

#endif

