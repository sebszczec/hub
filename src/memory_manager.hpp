#ifndef __MEMORY_MANAGER_HPP
#define __MEMORY_MANAGER_HPP

#include <map>

using namespace std;

class Block
{
public:
    static const int size = 128;

private:
    int _descriptor;
    char _buffer[size] = { 0 };

public:
    Block(int descriptor)
    : _descriptor(descriptor)
    {
    }

    int GetDescriptor()
    {
        return this->_descriptor;
    }

    void * GetPayload()
    {
        return &this->_buffer[0];
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

#endif
