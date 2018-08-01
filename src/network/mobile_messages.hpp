#ifndef __MOBILE_MESSAGES_HPP
#define __MOBILE_MESSAGES_HPP

#include <stdint.h>

typedef uint8_t OneByte;
typedef uint16_t TwoBytes;
typedef uint32_t FourBytes;

struct Message1
{
    OneByte ID;
    OneByte TRANSACTION;
    OneByte REQUEST[254];
};

struct Message1
{
    OneByte ID;
    OneByte TRANSACTION;
    TwoBytes RESPONSE;
};

#endif
