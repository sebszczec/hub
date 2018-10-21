#ifndef __MEMORY_MANAGER_HPP
#define __MEMORY_MANAGER_HPP

#include <map>
#include <mutex>
#include <stack>
#include <cstring>

using namespace std;

namespace machine
{

class InvalidLengthException : public exception
{
};

class Block
{
public:

private:
    unsigned int _descriptor = 0;
    unsigned int _length = 0;
    unsigned int _size = 0;
    char * _buffer = nullptr;

public:
    Block(unsigned int descriptor, unsigned int size)
    : _descriptor(descriptor), _size(size)
    {
        this->_buffer = new char[size];
        memset(this->_buffer, 0, size);
    }

    virtual ~Block()
    {
        delete[] this->_buffer;
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
        if (length > this->_size)
        {
            throw InvalidLengthException();
        }
        this->_length = length;
    }

    unsigned int GetMaxSize() const
    {
        return this->_size;
    }
};

class MemoryManager
{
private:
    static unsigned int _descriptorGenerator;
    const unsigned int _preallocationSize = 5;
    const unsigned int _preallocationMaxFreeSize = 10;

    const unsigned int _blockSize = 0;
    map<int, Block *> _blocks;
    int _allocatedBlocks = 0;
    std::mutex _mutex;
    std::stack<Block *> _preallocatedBlocks;

    static unsigned int GetNewDescriptor();
    void IncreaseMemoryPreallocation();
    void ReduceMemoryPreallocation();

public:
    MemoryManager();
    ~MemoryManager();

    Block * GetFreeBlock();
    void DeleteBlock(unsigned int descriptor);
    void DeleteBlock(Block * block);
    unsigned int GetAllocatedBlocks()
    {
        return this->_allocatedBlocks;
    }

    void DumpMemory();
};

} // namespace machine

#endif
