#ifndef __CONTEXT_MANAGER_TESTS_HPP
#define __CONTEXT_MANAGER_TESTS_HPP

#include <gtest/gtest.h>
#include "context_manager.hpp"
#include "system.hpp"

using namespace network;

class ContextManagerTest : public testing::Test 
{
protected:
    ContextManager * _sut = nullptr;
public:
    void SetUp() override
    {
        _sut = new ContextManager();
    }

    void TearDown() override
    {
        delete _sut;
        _sut = nullptr;
    }
};

TEST_F(ContextManagerTest, Instance)
{
    EXPECT_TRUE(_sut != nullptr);
}

TEST_F(ContextManagerTest, CreateContext)
{
    EXPECT_EQ(0u, _sut->GetActiveCountextCount());
    
    auto context1 = _sut->CreateContext();
    EXPECT_EQ(1u, _sut->GetActiveCountextCount());

    auto context2 = _sut->CreateContext();
    EXPECT_EQ(2u, _sut->GetActiveCountextCount());

    _sut->DeleteContext(context1);
    EXPECT_EQ(1u, _sut->GetActiveCountextCount());

    _sut->DeleteContext(context2);
    EXPECT_EQ(0u, _sut->GetActiveCountextCount());
}

TEST_F(ContextManagerTest, ContextContent)
{
    auto context = _sut->CreateContext();
    EXPECT_EQ(account::AccessLevel::Level::NotLogged, context->GetUser().GetAccessLevel().GetLevel());
}

#endif
