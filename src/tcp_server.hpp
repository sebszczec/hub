#ifndef __TELNET_SERVER
#define __TELNET_SERVER

#include <string>
#include <utility>
#include <libsocket/inetserverstream.hpp>
#include <libsocket/socket.hpp>
#include <libsocket/select.hpp>
#include <map>
#include "connection_manager.hpp"
#include "delegate.hpp"

using namespace std;
using libsocket::inet_socket;
using libsocket::inet_stream;
using libsocket::inet_stream_server;
using libsocket::selectset;

class TcpServer
{
private:
    string _prefix;
    string _host = "127.0.0.1";
    string _port;
    inet_stream_server * _server = nullptr;
    selectset<inet_socket> _readSet;
    bool _working = false;
    int _id = 0;

    static int _idGenerator;
    static map<int, TcpServer *> _instances;

    ConnectionManager _connectionManager;

    void ListenLoop();
    void HandleIncommingData(inet_socket & socket);

public:
    TcpServer() = delete;

    TcpServer(const string& port)
    : _id(TcpServer::_idGenerator++), _port(port)
    {
        TcpServer::_instances[this->_id] = this;
        this->_prefix = "TcpServer[" + std::to_string(this->_id) + "]";
    }

    TcpServer(string&& port)
    : _id(TcpServer::_idGenerator++), _port(port)
    {
        TcpServer::_instances[this->_id] = this;
        this->_prefix = "TcpServer[" + std::to_string(this->_id) + "]";
    }

    ~TcpServer();

    Delegate OnAddConnection;
    Delegate OnRemoveConnection;

    inline string GetExtendedPrefix(int descriptor)
    {
        return this->_prefix + "[" + std::to_string(descriptor) + "]";
    }

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

    void AddStream();
    void RemoveStream(const inet_stream& stream);

    static void StopAllInstances();
};

#endif
