#include "configuration_manager.hpp"
#include <iostream>
#include "system.hpp"

namespace machine
{

using CM = ConfigurationManager;
using CMV = CM::Variable;

CM::~ConfigurationManager()
{
    this->ClearResources();
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

    string mobilePort = this->_configFile.lookup("mobile_port");
    this->_resources[CMV::MobilePort] = new StringResource(mobilePort);

    int tcpPooling = this->_configFile.lookup("tcp_pooling");
    this->_resources[CMV::TcpPooling] = new IntResource(tcpPooling);

    int tcpooling = this->_configFile.lookup("tcp_cooling");
    this->_resources[CMV::TcpCooling] = new IntResource(tcpooling);

    string memoryDumpName = this->_configFile.lookup("memory_dump_name");
    this->_resources[CMV::MemoryDumpName] = new StringResource(memoryDumpName);

    string databaseFileName = this->_configFile.lookup("database_file_name");
    this->_resources[CMV::DatabaseFileName] = new StringResource(databaseFileName);

    return true;
}

IResource & CM::GetResource(CMV variableName)
{
    return  *this->_resources[variableName];
}

void CM::ClearResources()
{
    System::GetLogger()->Log("ConfigurationManager: cleaning resources");;
    for (auto &pair : this->_resources)
    {
        delete pair.second;
    }

    this->_resources.clear();
}

} // namespace machine

