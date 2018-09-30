#ifndef __MEMORY_MANAGER_TEST_HPP
#define __MEMORY_MANAGER_TEST_HPP

#include "memory_manager.hpp"
#include <gtest/gtest.h>
#include "system.hpp"

class MemoryManagerTest : public testing::Test 
{
protected:
    machine::MemoryManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new machine::MemoryManager();
    }

    void TearDown() override
    {
        delete _sut;
        _sut = nullptr;
    }

};

TEST_F(MemoryManagerTest, Instance)
{
    EXPECT_TRUE(_sut != nullptr);
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

TEST_F(MemoryManagerTest, Allocate)
{
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
    auto block1 = _sut->GetFreeBlock();
    EXPECT_EQ(1, _sut->GetAllocatedBlocks());
    auto block2 = _sut->GetFreeBlock();
    EXPECT_EQ(2, _sut->GetAllocatedBlocks());

    _sut->DeleteBlock(block1->GetDescriptor());
    EXPECT_EQ(1, _sut->GetAllocatedBlocks());

    _sut->DeleteBlock(block2->GetDescriptor());
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

TEST_F(MemoryManagerTest, AllocateStressTest)
{
    const unsigned int bufferSize = 1024;
    machine::Block * blocks[bufferSize];

    for (unsigned int i = 0; i < bufferSize; i++)
    {
        blocks[i] = _sut->GetFreeBlock();
    }
    EXPECT_EQ(bufferSize, _sut->GetAllocatedBlocks());

        for (unsigned int i = 0; i < bufferSize; i++)
    {
        _sut->DeleteBlock(blocks[i]->GetDescriptor());
    }
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

TEST_F(MemoryManagerTest, DeleteWrongDescriptor)
{
    auto block1 = _sut->GetFreeBlock();
    auto block2 = _sut->GetFreeBlock();

    auto descriptor = block1->GetDescriptor();
    _sut->DeleteBlock(descriptor);
    EXPECT_EQ(1, _sut->GetAllocatedBlocks());

    _sut->DeleteBlock(descriptor);
    EXPECT_EQ(1, _sut->GetAllocatedBlocks());

    _sut->DeleteBlock(block2->GetDescriptor());
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

TEST_F(MemoryManagerTest, InvalidBlockSize)
{
    auto block1 = _sut->GetFreeBlock();
    auto maxSize = block1->GetMaxSize();

    ASSERT_THROW(block1->SetPayloadLength(maxSize + 1), machine::InvalidLengthException);

    _sut->DeleteBlock(block1->GetDescriptor());
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

TEST_F(MemoryManagerTest, ValidBlockSize)
{
    auto block1 = _sut->GetFreeBlock();
    auto maxSize = block1->GetMaxSize();

    EXPECT_NO_THROW(block1->SetPayloadLength(maxSize));
    EXPECT_EQ(maxSize, block1->GetPayloadLength());

    _sut->DeleteBlock(block1->GetDescriptor());
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

#endif
