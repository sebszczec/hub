#include "logger.hpp"
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "strings.hpp"

namespace machine
{

Logger::Logger()
: _filename(""), _flushResolution(0), _flushCounter(0), _file(), _buffer(""), _logLevel(LogLevel::Debug), _mutex()
{
}

void Logger::Initilize(const std::string &filename, int flushResolution)
{
    this->_flushResolution = flushResolution;
    this->_filename = filename;

    this->_file.open(this->_filename, std::fstream::out | std::fstream::app);
}

void Logger::Initilize(const std::string &filename, int flushResolution, LogLevel logLevel)
{
    this->Initilize(filename, flushResolution);
    this->SetLogLevel(logLevel);
}

void Logger::ClearResources()
{
    this->Log("Logger: cleaning resources");
    this->Flush(true);
    this->_file.close();
}

void Logger::Flush(bool force)
{
    std::lock_guard<std::mutex> lock(this->_mutex);
    if (++this->_flushCounter >= this->_flushResolution || force)
    {
        this->_flushCounter = 0;
        this->_file << this->_buffer;
        this->_buffer = "";
        this->_file.flush();
        return;
    }
}

std::string Logger::CurrentTime()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);

    std::stringstream stringStream;
    stringStream << std::put_time(std::localtime(&in_time_t), machine::string::timeFormat.c_str());
    return stringStream.str();
}

void Logger::Log(const std::string &prefix, const std::string &text)
{
    auto tmp = CurrentTime() + " " + prefix + " " + text + machine::string::endl;

    {
        std::lock_guard<std::mutex> lock(this->_mutex);
        this->_buffer.append(tmp);
    }

    this->Flush();
}

void Logger::LogDebug(const std::string &text)
{
    if (this->_logLevel <= LogLevel::Debug)
    {
        this->Log(machine::string::dbg, text);
    }
}

void Logger::LogError(const std::string &text)
{
    if (this->_logLevel <= LogLevel::Error)
    {
        this->Log(machine::string::err, text);
    }
}

void Logger::Log(const std::string &text)
{
    if (this->_logLevel <= LogLevel::Info)
    {
        this->Log(machine::string::inf, text);
    }
}

} // namespace machine
