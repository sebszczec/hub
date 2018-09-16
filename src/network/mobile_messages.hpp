#ifndef __MOBILE_MESSAGES_HPP
#define __MOBILE_MESSAGES_HPP

#include <stdint.h>

namespace network
{

typedef uint8_t OneByte;
typedef uint16_t TwoBytes;
typedef uint32_t FourBytes;

static const unsigned int NetworkMessageSize = 128;
static const unsigned int HandshakeNameSize = 5;

enum MessageId
{
    HandshakeRequest,
    HandshakeResponse
};

struct NetworkMessage
{
    OneByte ID;
    OneByte REQUEST[NetworkMessageSize - 1];
};

struct HandshakeRequest
{
    FourBytes Name[HandshakeNameSize];
};

struct HandshakeResponse
{
    OneByte MobileId;
};

} // namespace network

#endif
