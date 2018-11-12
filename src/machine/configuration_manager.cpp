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
    return this->LoadResources("");
}

bool CM::LoadResources(string settingFile)
{
    if (settingFile.empty())
    {
        settingFile = "settings.cfg";
    }

    try
    {
        this->_configFile.readFile(settingFile.c_str());
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

    int telnetEnabled = this->_configFile.lookup("telnet_enabled");
    this->_resources[CMV::TelnetEnabled] = new BoolResource(telnetEnabled == 1);

    int telnetPort = this->_configFile.lookup("telnet_port");
    this->_resources[CMV::TelnetPort] = new IntResource(telnetPort);

    int telnetSSLEnabled = this->_configFile.lookup("telnet_ssl_enabled");
    this->_resources[CMV::TelnetSSLEnabled] = new BoolResource(telnetSSLEnabled == 1);

    int telnetSSLPort = this->_configFile.lookup("telnet_ssl_port");
    this->_resources[CMV::TelnetSSLPort] = new IntResource(telnetSSLPort);

    int mobileEnabled = this->_configFile.lookup("mobile_enabled");
    this->_resources[CMV::MobileEnabled] = new BoolResource(mobileEnabled == 1);

    int mobilePort = this->_configFile.lookup("mobile_port");
    this->_resources[CMV::MobilePort] = new IntResource(mobilePort);

    string sslCRTFile = this->_configFile.lookup("ssl_crt_file");
    this->_resources[CMV::SSLCRTFile] = new StringResource(sslCRTFile);

    string sslKeyFile = this->_configFile.lookup("ssl_key_file");
    this->_resources[CMV::SSLKeyFile] = new StringResource(sslKeyFile);

    string sslDhFile = this->_configFile.lookup("ssl_dh_file");
    this->_resources[CMV::SSLDhFile] = new StringResource(sslDhFile);

    string sslPassword = this->_configFile.lookup("ssl_password");
    this->_resources[CMV::SSLPassword] = new StringResource(sslPassword);

    string memoryDumpName = this->_configFile.lookup("memory_dump_name");
    this->_resources[CMV::MemoryDumpName] = new StringResource(memoryDumpName);

    int memoryBlockSize = this->_configFile.lookup("memory_block_size");
    this->_resources[CMV::MemoryBlockSize] = new IntResource(memoryBlockSize);

    int memoryPreallocatedSize = this->_configFile.lookup("memory_preallocation_size");
    this->_resources[CMV::MemoryPreallocatedSize] = new IntResource(memoryPreallocatedSize);

    int memoryMaxFreePreallocatedSize = this->_configFile.lookup("memory_free_preallocated_size");
    this->_resources[CMV::MemoryMaxFreePreallocatedSize] = new IntResource(memoryMaxFreePreallocatedSize);

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

