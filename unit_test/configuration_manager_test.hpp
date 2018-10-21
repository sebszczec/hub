#ifndef __CONFIGURATION_MANAGER_TEST_HPP
#define __CONFIGURATION_MANAGER_TEST_HPP

#include <gtest/gtest.h>
#include "configuration_manager.hpp"
#include <iostream>

class ConfigurationManagerTest : public testing::Test
{
public:
};


TEST_F(ConfigurationManagerTest, IntResource)
{
    auto value = 20;
    machine::IntResource sut(value);

    EXPECT_EQ(value, sut.ToInt());
}

TEST_F(ConfigurationManagerTest, IntResourceExceptionString)
{
    auto value = 20;
    machine::IntResource sut(value);

    EXPECT_THROW(sut.ToString(), machine::WrongTypeException);
}

TEST_F(ConfigurationManagerTest, IntResourceExceptionBool)
{
    auto value = 20;
    machine::IntResource sut(value);

    EXPECT_THROW(sut.ToBool(), machine::WrongTypeException);
}

TEST_F(ConfigurationManagerTest, StringResource)
{
    string value = "20";
    machine::StringResource sut(value);

    EXPECT_STREQ(value.c_str(), sut.ToString().c_str());
}

TEST_F(ConfigurationManagerTest, StringResourceExceptionInt)
{
    string value = "20";
    machine::StringResource sut(value);

    EXPECT_THROW(sut.ToInt(), machine::WrongTypeException);
}

TEST_F(ConfigurationManagerTest, StringResourceExceptionBool)
{
    string value = "20";
    machine::StringResource sut(value);

    EXPECT_THROW(sut.ToBool(), machine::WrongTypeException);
}

TEST_F(ConfigurationManagerTest, BoolResource)
{
    auto value = true;
    machine::BoolResource sut(value);

    EXPECT_TRUE(sut.ToBool());
}

TEST_F(ConfigurationManagerTest, BoolResourceExceptionString)
{
    auto value = true;
    machine::BoolResource sut(value);

    EXPECT_THROW(sut.ToString(), machine::WrongTypeException);
}

TEST_F(ConfigurationManagerTest, BoolResourceExceptionInt)
{
    auto value = true;
    machine::BoolResource sut(value);

    EXPECT_THROW(sut.ToInt(), machine::WrongTypeException);
}

#endif // __CONFIGURATION_MANAGER_TEST_HPP