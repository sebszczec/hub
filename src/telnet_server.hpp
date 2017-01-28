#ifndef __TELNET_SERVER
#define __TELNET_SERVER

#include <string>
#include <utility>
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>
#include <libsocket/select.hpp>
#include <map>

using namespace std;
using libsocket::inet_socket;
using libsocket::inet_stream;
using libsocket::inet_stream_server;
using libsocket::selectset;

class TelnetServer
{
private:
    string _host = "127.0.0.1";
    string _port;
    inet_stream_server * _server = nullptr;
    selectset<inet_socket> _readSet;
    bool _working = false;
    int _id = 0;

    static int _idGenerator;
    static map<int, TelnetServer *> _instances;

public:
    TelnetServer()
    : _id(TelnetServer::_idGenerator++)
    {
        TelnetServer::_instances[this->_id] = this;
    }

    TelnetServer(const string& port)
    : _id(TelnetServer::_idGenerator++),  _port(port)
    {
        TelnetServer::_instances[this->_id] = this;
    }

    TelnetServer(string&& port)
    : _id(TelnetServer::_idGenerator++), _port(port)
    {
        TelnetServer::_instances[this->_id] = this;
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

    static void StopAllInstances();
};

#endif
