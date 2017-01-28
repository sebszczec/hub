#ifndef __TELNET_SERVER
#define __TELNET_SERVER

#include <string>
#include <utility>
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>
#include <libsocket/select.hpp>

using namespace std;
using libsocket::inet_stream_server;
using libsocket::selectset;

class TelnetServer
{
private:
    string _host = "127.0.0.1";
    string _port;
    inet_stream_server * _server = nullptr;
    selectset<inet_stream_server> _readSet;
    bool _working = false;

public:
    TelnetServer() = default;
    TelnetServer(const string& port)
    : _port(port)
    {
    }

    TelnetServer(string&& port)
    : _port(port)
    {
    }

    ~TelnetServer();

    string GetPort()
    {
        return this->_port;
    }

    void SetPort(const string& port)
    {
        this->_port = port;
    }

    void SetPort(string&& port)
    {
        this->_port = port;
    }

    void Start();

    void Stop();
};

#endif
