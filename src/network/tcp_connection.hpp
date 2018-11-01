#ifndef __TCP_CONNECTION_HPP
#define __TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "system.hpp"

namespace network
{

using boost::asio::ip::tcp;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class TcpBase;

class TcpSocket
{
private:
    tcp::socket _socket;
    ssl_socket _sslSocket;
    bool _ssl = false;

public:
    TcpSocket(boost::asio::io_service& ios, boost::asio::ssl::context& context)
    : _socket(ios),
    _sslSocket(ios, context)
    {}

    boost::asio::ip::tcp::socket::lowest_layer_type & GetLowestLayerSocket()
    {
        if (this->IsSSL())
        {
            return this->_sslSocket.lowest_layer();
        }

        return this->_socket.lowest_layer();
    }

    tcp::socket & GetTcpSocket()
    {
        return this->_socket;
    }

    ssl_socket & GetSSLSocket()
    {
        return this->_sslSocket;
    }

    bool IsSSL()
    {
        return this->_ssl;
    }

    void SetSSLflag(bool flag)
    {
        this->_ssl = flag;
    }
};

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
protected:
    Context * _context = nullptr;
    machine::Block * _memoryBlock = nullptr;
    TcpSocket _socket;
    TcpBase & _parent;

    void HandleWrite(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    void HandleRead(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    void HandleHandShake(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& error);
    
public:
    TcpConnection(boost::asio::io_service& ios, TcpBase & parent, boost::asio::ssl::context & sslContext);
    virtual ~TcpConnection();

    virtual void Start();
    virtual void Stop();
    void SendData(const void * data, unsigned int size);
    
    virtual void HandleData() = 0;
    boost::asio::ip::tcp::socket::lowest_layer_type & GetSocket();
    Context & GetContext();
};

} // namespace network

#endif // __TCP_CONNECTION_HPP