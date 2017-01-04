#include <libconfig.h++>

using namespace libconfig;

class ConfigurationManager
{
    ConfigurationManager() = delete;
    ~ConfigurationManager() = delete;

    static Config _configFile;
public:
    static bool LoadResources();
};