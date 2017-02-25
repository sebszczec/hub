#ifndef __MEMORY_MANAGER_TEST_HPP
#define __MEMORY_MANAGER_TEST_HPP

#include "memory_manager.hpp"
#include <gtest/gtest.h>

class MemoryManagerTest : public testing::Test 
{
protected:
    MemoryManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = MemoryManager::GetInstance();
    }

    void TearDown() override
    {
        MemoryManager::DeleteInstance();
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

    ASSERT_THROW(block1->SetPayloadLength(maxSize + 1), InvalidLengthException);

    _sut->DeleteBlock(block1->GetDescriptor());
    EXPECT_EQ(0, _sut->GetAllocatedBlocks());
}

#endif
