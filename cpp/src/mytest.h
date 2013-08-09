////////////////////////////////////////////////////////////////////////////
/// @file    mytest.h
/// @brief   common unit test helpers
/// @author  qianguoxiang2008@gmail.com
/// @date    2012-05-22
/// @version 1.0
////////////////////////////////////////////////////////////////////////////

#ifndef __MYTEST_H__
#define __MYTEST_H__

#include "gtest/gtest.h"

#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"

#define ERRMSG(const_msg) "\033[0;31m     `--> " const_msg "\033[0m"

#define SIZEOFARRAY(arr) \
    (sizeof(arr) / sizeof(arr[0]))

#endif // __MYTEST_H__

