#ifndef __TCP_CONNECTION_HPP
#define __TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "system.hpp"

namespace network
{

using boost::asio::ip::tcp;

class TcpConnectionStorage;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
protected:
    Context * _context = nullptr;
    machine::Block * _memoryBlock = nullptr;
    tcp::socket _socket;
    TcpConnectionStorage & _parent;

    void HandleWrite(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    void HandleRead(std::shared_ptr<TcpConnection>& connection, const boost::system::error_code& err, size_t bytesTransferred);
    
public:
    TcpConnection(boost::asio::io_service& ios, TcpConnectionStorage & parent)
    : _context(machine::System::GetContextManager()->CreateContext()),
      _memoryBlock(machine::System::GetMemoryManager()->GetFreeBlock()), 
      _socket(ios),
      _parent(parent)
    {
    }

    virtual ~TcpConnection();

    virtual void Start();
    virtual void Stop();
    void SendData(const void * data, unsigned int size);
    
    virtual void HandleData() = 0;
    
    tcp::socket& GetSocket();
    Context & GetContext();
};

} // namespace network

#endif // __TCP_CONNECTION_HPP