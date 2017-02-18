#ifndef __CONNECTION_MANAGER_HPP
#define __CONNECTION_MANAGER_HPP

class Connection
{
    int _socketFd = 0;
public:
    Connection(int socketFd)
    : _socketFd(socketFd)
    {}

    ~Connection() = default;
};

class ConnectionManager
{
public:
    ConnectionManager() = default;
    ~ConnectionManager() = default;

    void AddConnect(int socketFd);
    void RemoveConnection(int socketFd);
};

#endif