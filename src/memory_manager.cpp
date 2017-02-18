#include "memory_manager.hpp"
#include "configuration_manager.hpp"
#include <fstream>
#include "logger.hpp"

MemoryManager * MemoryManager::_instance = nullptr;
int MemoryManager::_descriptorGenerator = 0;

MemoryManager::~MemoryManager()
{
    for (auto & pair : this->_blocks)
    {
        delete pair.second;
    }

    this->_blocks.clear();
    _allocatedBlocks = 0;
}

MemoryManager * MemoryManager::GetInstance()
{
    if (MemoryManager::_instance == nullptr)
    {
        MemoryManager::_instance = new MemoryManager();
    } 

    return MemoryManager::_instance;
}

void MemoryManager::DeleteInstance()
{
    if (MemoryManager::_instance != nullptr)
    {
        delete MemoryManager::_instance;
        MemoryManager::_instance = nullptr;
    }
}

int MemoryManager::GetNewDescriptor()
{
    return MemoryManager::_descriptorGenerator++;
}

Block * MemoryManager::GetFreeBlock()
{
    auto block = new Block(MemoryManager::GetNewDescriptor());
    this->_blocks[block->GetDescriptor()] = block;

    _allocatedBlocks++;

    return block;
}

void MemoryManager::DeleteBlock(int descriptor)
{
    auto block = this->_blocks.find(descriptor);
    if (block == this->_blocks.end())
    {
        return;
    }

    _allocatedBlocks--;

    delete block->second;
    this->_blocks.erase(block);
}

void MemoryManager::DumpMemory()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    auto name = CM::GetResource(CMV::MemoryDumpName).ToString();
    Logger::Log("MemoryManager: dumping the memory to " + name);

    fstream file;
    file.open(CM::GetResource(CMV::MemoryDumpName).ToString(), std::fstream::out | std::fstream::trunc);

    file << "Allocated blocks: " << this->GetAllocatedBlocks() << std::endl;

    for (auto pair : this->_blocks)
    {
        file << "Block descriptor: " << pair.first << ", size: " << pair.second->GetPayloadLength() << std::endl;
        char * buffer = reinterpret_cast<char *>(pair.second->GetPayload());
        for (int i = 0; i < pair.second->size; i++)
        {
            file << buffer[i];
        }
        file << std::endl;
    }

    file.close();
}