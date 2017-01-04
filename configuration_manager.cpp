#include "configuration_manager.hpp"
#include <iostream>

Config ConfigurationManager::_configFile;
set<ConfigurationManager::Variable, IResource *> ConfigurationManager::_resources;

bool ConfigurationManager::LoadResources()
{
    try
    {
        ConfigurationManager::_configFile.readFile("settings.cfg");
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

    return true;
}
