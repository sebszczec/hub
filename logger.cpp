#include "logger.hpp"

std::string Logger::_filename = "";
int Logger::_flushResolution = 0;
int Logger::_flushCounter = 0;
std::fstream Logger::_file;
std::string Logger::_buffer = "";

void Logger::Initilize(const std::string &filename, int flushResolution)
{
    Logger::_flushResolution = flushResolution;
    Logger::_filename = filename;

    Logger::_file.open(Logger::_filename, std::fstream::out | std::fstream::app);
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

void Logger::LogDebug(const std::string &)
{

}

void Logger::LogError(const std::string &)
{

}

void Logger::Log(const std::string &text)
{
    std::string tmp = "INFO " + text + "\n";
    Logger::_buffer.append(tmp);

    Logger::Flush();
}