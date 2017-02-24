#include "configuration_manager.hpp"
#include <iostream>
#include "logger.hpp"

using CM = ConfigurationManager;
using CMV = CM::Variable;

ConfigurationManager * CM::_instance = nullptr;

CM::~ConfigurationManager()
{
    if (CM::_instance != nullptr)
    {
        delete CM::_instance;
        CM::_instance = nullptr;
    }
}

ConfigurationManager * CM::GetInstance()
{
    if(CM::_instance == nullptr)
    {
        CM::_instance = new ConfigurationManager();
    }

    return CM::_instance;
}

bool CM::LoadResources()
{
    try
    {
        this->_configFile.readFile("settings.cfg");
    }
    catch (const FileIOException &exception)
    {
        std::cerr << "I/O error while reading config file." << std::endl;
        return false;
    }
    catch (const ParseException &exception)
    {
        std::cerr << "Config file parse error at " << exception.getFile() << ":" << exception.getLine() << " - " << exception.getError() << std::endl;
        return false;
    }

    string logName = this->_configFile.lookup("log_name");
    this->_resources[CMV::LogFileName] = new StringResource(logName);

    int logLevel = this->_configFile.lookup("log_level");
    this->_resources[CMV::LogLevel] = new IntResource(logLevel);

    int logResolution = this->_configFile.lookup("log_resolution");
    this->_resources[CMV::LogResolution] = new IntResource(logResolution);

    string pidName = this->_configFile.lookup("pid_name");
    this->_resources[CMV::PidFileName] = new StringResource(pidName);

    int isDaemon = this->_configFile.lookup("daemon");
    this->_resources[CMV::IsDaemon] = new BoolResource(isDaemon == 1);

    string telnetPort = this->_configFile.lookup("telnet_port");
    this->_resources[CMV::TelnetPort] = new StringResource(telnetPort);

    int telnetPooling = this->_configFile.lookup("telnet_pooling");
    this->_resources[CMV::TelnetPooling] = new IntResource(telnetPooling);

    int telnetCooling = this->_configFile.lookup("telnet_cooling");
    this->_resources[CMV::TelnetCooling] = new IntResource(telnetCooling);

    string memoryDumpName = this->_configFile.lookup("memory_dump_name");
    this->_resources[CMV::MemoryDumpName] = new StringResource(memoryDumpName);

    return true;
}

IResource & CM::GetResource(CMV variableName)
{
    return  *this->_resources[variableName];
}

void CM::ClearResources()
{
    Logger::Log("ConfigurationManager: cleaning resources");;
    for (auto &pair : this->_resources)
    {
        delete pair.second;
    }

    this->_resources.clear();
}
