#include "mobile_connection.hpp"
#include "mobile_messages.hpp"
#include "mobile_messages.pb.h"
#include "strings.hpp"
#include <iomanip>

namespace network
{

void MobileConnection::Start()
{
    TcpConnection::Start();
    this->GetContext().GetUser().SetUserType(account::User::UserType::Mobile);
}

void MobileConnection::HandleData() 
{
    auto logger = machine::System::GetLogger();

    auto packetLength = this->_memoryBlock->GetPayloadLength();
    logger->LogDebug(::machine::string::mobileConnectionMessage1 + std::to_string(packetLength));

    auto dataArray = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

    mobile_messages::NetworkMessage message;
    if (message.ParseFromArray(dataArray, packetLength))
    {
        logger->LogDebug(::machine::string::mobileConnectionMessage2);
    }
    else
    {
        logger->LogError(::machine::string::mobileConnectionMessage3);
    }

    switch (message.messageid())
    {
        case network::MessageId::HandshakeRequest:
        logger->Log(::machine::string::mobileConnectionMessage4);
        break;

        default:
        logger->LogError(::machine::string::mobileConnectionMessage5 + std::to_string(message.messageid()));
        break;
    }
}

} // namespace network
