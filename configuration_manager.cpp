#include "configuration_manager.hpp"
#include <iostream>

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

    return true;
}

IResource * CM::GetResource(CMV variableName)
{
    return  CM::_resources[variableName];
}
