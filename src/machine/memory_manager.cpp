#include "memory_manager.hpp"
#include "system.hpp"
#include <fstream>
#include <mutex>

namespace machine
{

unsigned int MemoryManager::_descriptorGenerator = 0;

MemoryManager::MemoryManager()
{
    using CM = ConfigurationManager;
    using CMV = CM::Variable;

    this->_blockSize = System::GetConfigurationManager()->GetResource(CMV::MemoryBlockSize).ToInt();
    this->IncreaseMemoryPreallocation();
}

MemoryManager::~MemoryManager()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    while (!this->_preallocatedBlocks.empty())
    {
        auto block = this->_preallocatedBlocks.top();
        this->_preallocatedBlocks.pop();
        delete block;
    }

    this->_blocks.clear();
    _allocatedBlocks = 0;
}

void MemoryManager::IncreaseMemoryPreallocation()
{
    for (unsigned int i = 0; i < this->_preallocationSize; i++)
    {
        this->_preallocatedBlocks.push(new Block(MemoryManager::GetNewDescriptor(), this->_blockSize));
    }
}

void MemoryManager::ReduceMemoryPreallocation()
{
    while (this->_preallocatedBlocks.size() > this->_preallocationSize)
    {
        auto block = this->_preallocatedBlocks.top();
        this->_preallocatedBlocks.pop();

        delete block;
    }
}

unsigned int MemoryManager::GetNewDescriptor()
{
    return MemoryManager::_descriptorGenerator++;
}

Block * MemoryManager::GetFreeBlock()
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    if (this->_preallocatedBlocks.empty())
    {
        this->IncreaseMemoryPreallocation();
    }
    auto block = this->_preallocatedBlocks.top();
    this->_preallocatedBlocks.pop();

    this->_blocks[block->GetDescriptor()] = block;

    _allocatedBlocks++;

    return block;
}

void MemoryManager::DeleteBlock(unsigned int descriptor)
{
    std::lock_guard<std::mutex> guard(this->_mutex);

    auto block = this->_blocks.find(descriptor);
    if (block == this->_blocks.end())
    {
        return;
    }

    _allocatedBlocks--;

    this->_preallocatedBlocks.push(block->second);
    this->_blocks.erase(block);

    if (this->_preallocatedBlocks.size() > this->_preallocationMaxFreeSize)
    {
        this->ReduceMemoryPreallocation();
    }
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
            for (unsigned int i = 0; i < pair.second->GetMaxSize(); i++)
            {
                file << buffer[i];
            }
            file << std::endl;
        }

        file << "Pre-allocation buffer size: " << this->_preallocatedBlocks.size() << std::endl;
    }

    file.close();
}

} // namespace machine
