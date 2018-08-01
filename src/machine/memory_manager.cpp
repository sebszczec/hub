#include "memory_manager.hpp"
#include "system.hpp"
#include <fstream>
#include <mutex>

namespace machine
{

int MemoryManager::_descriptorGenerator = 0;

MemoryManager::~MemoryManager()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    for (auto & pair : this->_blocks)
    {
        delete pair.second;
    }

    this->_blocks.clear();
    _allocatedBlocks = 0;
}

int MemoryManager::GetNewDescriptor()
{
    return MemoryManager::_descriptorGenerator++;
}

Block * MemoryManager::GetFreeBlock()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    auto block = new Block(MemoryManager::GetNewDescriptor());
    this->_blocks[block->GetDescriptor()] = block;

    _allocatedBlocks++;

    return block;
}

void MemoryManager::DeleteBlock(int descriptor)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

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
    auto configurationManager = System::GetConfigurationManager();

    auto name = configurationManager->GetResource(CMV::MemoryDumpName).ToString();
    System::GetLogger()->Log("MemoryManager: dumping the memory to " + name);

    fstream file;
    file.open(configurationManager->GetResource(CMV::MemoryDumpName).ToString(), std::fstream::out | std::fstream::trunc);

    file << "Allocated blocks: " << this->GetAllocatedBlocks() << std::endl;

    {
        std::lock_guard<std::mutex> guard(this->_mutex);
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
    }

    file.close();
}

} // namespace machine
