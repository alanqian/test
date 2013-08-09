////////////////////////////////////////////////////////////////////////////
/// @file    VolumeUT.cpp
/// @brief   unit test for class Volume
/// @author  qianguoxiang@snda.com
/// @date    2011-06-08
/// @version 1.0
////////////////////////////////////////////////////////////////////////////


#include <string.h>
#include "mytest.h"

using namespace std;

class foo_test : public testing::Test
{
protected:
    /// @brief SetUp Be invoked before each case.
    virtual void SetUp()
    {
        cout << ". setup\n";
        ASSERT_TRUE(NULL != _dc);
    }

    /// @brief TearDown Be invoked before each case.
    virtual void TearDown()
    {
        cout << ". teardown\n";
    }

    /// @brief SetUpTestCase Be invoked before each fixture.
    static void SetUpTestCase()
    {
        cout << "########################## Test Fixture Setup ######################" << std::endl;
        system("rm -rf *.log ./meta");
        system("mkdir ./meta");
        try
        {
            log4cxx::PropertyConfigurator::configure("logger.conf");
        }
        catch(log4cxx::helpers::Exception& e)
        {
            std::cout<< "error"<<std::endl;
        }
        LOG4CXX_TRACE(logger, format("foo_test start"));
    }

    /// @brief TearDownTestCase Be invoked Before each fixture.
    static void TearDownTestCase()
    {
        cout << "########################## Test Fixture TearDown ###################" << std::endl;
    }


protected:
    int _test;
};

//
TEST_F(foo_test, method1)
{
    EXPECT_EQ(1, 1) << ERRMSG("verify method1");
}

TEST_F(foo_test, method2)
{
    EXPECT_EQ(1, 1) << ERRMSG("verify method2");
}

