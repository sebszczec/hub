#include "logger.hpp"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string Logger::_filename = "";
int Logger::_flushResolution = 0;
int Logger::_flushCounter = 0;
std::fstream Logger::_file;
std::string Logger::_buffer = "";
LogLevel Logger::_logLevel = LogLevel::Debug;

void Logger::Initilize(const std::string &filename, int flushResolution)
{
    Logger::_flushResolution = flushResolution;
    Logger::_filename = filename;

    Logger::_file.open(Logger::_filename, std::fstream::out | std::fstream::app);
}

void Logger::Initilize(const std::string &filename, int flushResolution, LogLevel logLevel)
{
    Logger::Initilize(filename, flushResolution);
    Logger::SetLogLevel(logLevel);
}

void Logger::Flush()
{
    if (++Logger::_flushCounter >= Logger::_flushResolution)
    {
        Logger::_flushCounter = 0;
        Logger::_file << Logger::_buffer;
        Logger::_file.flush();
        return;
    }
}

std::string Logger::CurrentTime()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);

    std::stringstream stringStream;
    stringStream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return stringStream.str();
}

void Logger::Log(const std::string &prefix, const std::string &text)
{
    auto tmp = CurrentTime() + " " + prefix + " " + text + "\n";
    Logger::_buffer.append(tmp);

    Logger::Flush();
}

void Logger::LogDebug(const std::string &text)
{
    if (Logger::_logLevel <= LogLevel::Debug)
    {
        Logger::Log("DBG", text);
    }
}

void Logger::LogError(const std::string &text)
{
    if (Logger::_logLevel <= LogLevel::Error)
    {
        Logger::Log("ERR", text);
    }
}

void Logger::Log(const std::string &text)
{
    if (Logger::_logLevel <= LogLevel::Info)
    {
        Logger::Log("INF", text);
    }
}