#include <libconfig.h++>
#include <string>
#include <exception>
#include <map>

using namespace libconfig;
using namespace std;

class WrongTypeException : public exception
{

};

class IResource
{
public:
    IResource() = default;
    virtual ~IResource() {}

    virtual int ToInt() = 0;
    virtual string ToString() = 0;
};

class IntResource : public IResource
{
private:
    int _value = 0;
public:
    IntResource(int value)
    : _value(value) {}

    ~IntResource() {}

    int ToInt() override
    {
        return this->_value;
    }

    string ToString() override
    {
        throw WrongTypeException();
    }
};

class StringResource : public IResource
{
private:
    string _value = "";
public:
    StringResource(string value)
    : _value(value) {}
    ~StringResource() {}

    int ToInt() override
    {
        throw WrongTypeException();
    }

    string ToString() override
    {
        return this->_value;
    }
};

class ConfigurationManager
{
public:
    enum Variable
    {
        LogFileName,
        LogLevel,
        LogResolution
    };

    static bool LoadResources();
    static IResource * GetResource(ConfigurationManager::Variable variableName);

private:
    ConfigurationManager() = delete;
    ~ConfigurationManager() = delete;

    static Config _configFile;

    using ResourceDictionary = map<ConfigurationManager::Variable, IResource *>;
    static ResourceDictionary _resources;
};