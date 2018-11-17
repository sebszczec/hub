#include "mobile_connection.hpp"
#include "mobile_messages.hpp"
#include "mobile_messages.pb.h"
#include <iomanip>

namespace network
{

void MobileConnection::HandleData() 
{
    auto logger = machine::System::GetLogger();
    logger->LogDebug("MobileConnection: Received data block");

    auto packetLength = this->_memoryBlock->GetPayloadLength();
    logger->LogDebug("MobileConnection: Network packet size: " + std::to_string(packetLength));

    auto array = reinterpret_cast<char *>(this->_memoryBlock->GetPayload());

    mobile_messages::NetworkMessage message;
    if (message.ParseFromArray(array, packetLength))
    {
        logger->LogDebug("MobileConnection: NetworkMessage succeded");
    }
    else
    {
        logger->LogDebug("MobileConnection: NetworkMessage failed");
    }

    switch (message.messageid())
    {
        case network::MessageId::HandshakeRequest:
        logger->Log("MobileConnection: HandshakeRequest received");
        break;

        default:
        logger->LogError("MobileConnection: Unknown network message: " + std::to_string(message.messageid()));
        break;
    }
}

} // namespace network
