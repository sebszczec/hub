#include "mobile_connection.hpp"
#include "mobile_messages.hpp"

namespace network
{

void MobileConnection::HandleData() 
{
    auto logger = machine::System::GetLogger();
    logger->LogDebug("MobileConnection: Received data block");

    auto packetLength = this->_memoryBlock->GetPayloadLength();
    if (packetLength != network::NetworkMessageSize)
    {
        logger->LogError("MobileConnection: Wrong network packet size: " + std::to_string(packetLength));
        throw WrongPacketSizeException();
        return; 
    }

    auto networkMessage = reinterpret_cast<NetworkMessage *>(this->_memoryBlock->GetPayload());

    switch (networkMessage->ID)
    {
        case network::MessageId::HandshakeRequest:
        logger->Log("MobileConnection: HandshakeRequest received");
        break;

        default:
        logger->LogError("MobileConnection: Unknown network message ID: " + std::to_string(networkMessage->ID));
        break;
    }
}

} // namespace network
