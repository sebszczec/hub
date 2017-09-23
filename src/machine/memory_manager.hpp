#ifndef __MEMORY_MANAGER_HPP
#define __MEMORY_MANAGER_HPP

#include <map>

using namespace std;

namespace machine
{

class InvalidLengthException : public exception
{
};

class Block
{
public:
    static const int size = 128;

private:
    int _descriptor = 0;
    int _length = 0;
    char _buffer[size] = { 0 };

public:
    Block(int descriptor)
    : _descriptor(descriptor)
    {
    }

    int GetDescriptor() const
    {
        return this->_descriptor;
    }

    void * GetPayload()
    {
        return &this->_buffer[0];
    }

    int GetPayloadLength() const
    {
        return this->_length;
    }

    void SetPayloadLength(int length)
    {
        if (length > size)
        {
            throw InvalidLengthException();
        }
        this->_length = length;
    }

    int GetMaxSize() const
    {
        return size;
    }
};

class MemoryManager
{
private:
    static MemoryManager * _instance;
    static int _descriptorGenerator;
    
    MemoryManager() = default;
    ~MemoryManager();

    map<int, Block *> _blocks;
    int _allocatedBlocks = 0;

    static int GetNewDescriptor();
public:
    static MemoryManager * GetInstance();    
    static void DeleteInstance();

    Block * GetFreeBlock();
    void DeleteBlock(int descriptor);
    int GetAllocatedBlocks()
    {
        return this->_allocatedBlocks;
    }

    void DumpMemory();
};

} // namespace machine

#endif
