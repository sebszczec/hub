#include "configuration_manager.hpp"
#include <iostream>
#include "logger.hpp"

using CM = ConfigurationManager;
using CMV = CM::Variable;

Config CM::_configFile;
CM::ResourceDictionary CM::_resources;

bool CM::LoadResources()
{
    try
    {
        CM::_configFile.readFile("settings.cfg");
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

    string logName = CM::_configFile.lookup("log_name");
    CM::_resources[CMV::LogFileName] = new StringResource(logName);

    int logLevel = CM::_configFile.lookup("log_level");
    CM::_resources[CMV::LogLevel] = new IntResource(logLevel);

    int logResolution = CM::_configFile.lookup("log_resolution");
    CM::_resources[CMV::LogResolution] = new IntResource(logResolution);

    string pidName = CM::_configFile.lookup("pid_name");
    CM::_resources[CMV::PidFileName] = new StringResource(pidName);

    int isDaemon = CM::_configFile.lookup("daemon");
    CM::_resources[CMV::IsDaemon] = new BoolResource(isDaemon == 1);

    string telnetPort = CM::_configFile.lookup("telnet_port");
    CM::_resources[CMV::TelnetPort] = new StringResource(telnetPort);

    int telnetPooling = CM::_configFile.lookup("telnet_pooling");
    CM::_resources[CMV::TelnetPooling] = new IntResource(telnetPooling);

    int telnetCooling = CM::_configFile.lookup("telnet_cooling");
    CM::_resources[CMV::TelnetCooling] = new IntResource(telnetCooling);

    return true;
}

IResource & CM::GetResource(CMV variableName)
{
    return  *CM::_resources[variableName];
}

void CM::ClearResources()
{
    Logger::Log("ConfigurationManager: cleaning resources");;
    for (auto &pair : CM::_resources)
    {
        delete pair.second;
    }

    CM::_resources.clear();
}
