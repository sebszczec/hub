#ifndef __MEMORY_MANAGER_HPP
#define __MEMORY_MANAGER_HPP

#include <map>
#include <mutex>

using namespace std;

namespace machine
{

class InvalidLengthException : public exception
{
};

class Block
{
public:
    static const unsigned int size = 128;

private:
    unsigned int _descriptor = 0;
    unsigned int _length = 0;
    char _buffer[size] = { 0 };

public:
    Block(unsigned int descriptor)
    : _descriptor(descriptor)
    {
    }

    unsigned int GetDescriptor() const
    {
        return this->_descriptor;
    }

    void * GetPayload()
    {
        return &this->_buffer[0];
    }

    unsigned int GetPayloadLength() const
    {
        return this->_length;
    }

    void SetPayloadLength(unsigned int length)
    {
        if (length > size)
        {
            throw InvalidLengthException();
        }
        this->_length = length;
    }

    unsigned int GetMaxSize() const
    {
        return size;
    }
};

class MemoryManager
{
private:
    static unsigned int _descriptorGenerator;

    map<int, Block *> _blocks;
    int _allocatedBlocks = 0;
    std::mutex _mutex;

    static unsigned int GetNewDescriptor();

public:
    MemoryManager() = default;
    ~MemoryManager();

    Block * GetFreeBlock();
    void DeleteBlock(unsigned int descriptor);
    unsigned int GetAllocatedBlocks()
    {
        return this->_allocatedBlocks;
    }

    void DumpMemory();
};

} // namespace machine

#endif
