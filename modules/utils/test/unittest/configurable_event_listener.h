/*
 * Copyright (c) 2014, German Aerospace Center (DLR)
 * All Rights Reserved.
 *
 * See the file "LICENSE" for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef UNITTEST_CONFIGURABLE_EVENT_LISTENER_H
#define UNITTEST_CONFIGURABLE_EVENT_LISTENER_H

#include <gtest/gtest.h>
#include <stdio.h>

// exported from gtest.cc to provide colored output
namespace testing
{
namespace internal
{
enum GTestColor
{
  COLOR_DEFAULT,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW
};

void ColoredPrintf(GTestColor color, const char* fmt, ...);
}
}

namespace unittest
{
class ConfigurableEventListener : public testing::TestEventListener
{
public:
    inline explicit
    ConfigurableEventListener(TestEventListener* theEventListener) :
        showTestCases(false),
        showTestNames(false),
        showSuccesses(false),
        showInlineFailures(true),
        showEnvironment(false),
        eventListener(theEventListener)
    {
    }

    virtual
    ~ConfigurableEventListener()
    {
    }

    virtual void
    OnTestProgramStart(const testing::UnitTest& unit_test)
    {
        eventListener->OnTestProgramStart(unit_test);
    }

    virtual void
    OnTestIterationStart(const testing::UnitTest& unit_test, int iteration)
    {
        eventListener->OnTestIterationStart(unit_test, iteration);
        printf("\n");
    }

    virtual void
    OnEnvironmentsSetUpStart(const testing::UnitTest& unit_test)
    {
        if (showEnvironment)
        {
            eventListener->OnEnvironmentsSetUpStart(unit_test);
        }
    }

    virtual void
    OnEnvironmentsSetUpEnd(const testing::UnitTest& unit_test)
    {
        if (showEnvironment)
        {
            eventListener->OnEnvironmentsSetUpEnd(unit_test);
        }
    }

    virtual void
    OnTestCaseStart(const testing::TestCase& test_case)
    {
        if (showTestCases)
        {
            eventListener->OnTestCaseStart(test_case);
        }
    }

    virtual void
    OnTestStart(const testing::TestInfo& test_info)
    {
        if (showTestNames)
        {
            eventListener->OnTestStart(test_info);
        }
    }

    virtual void
    OnTestPartResult(const testing::TestPartResult& result)
    {
        eventListener->OnTestPartResult(result);
    }

    virtual void
    OnTestEnd(const testing::TestInfo& test_info)
    {
        if (showInlineFailures && test_info.result()->Failed())
        {
            testing::internal::ColoredPrintf(testing::internal::COLOR_RED, "[  FAILED  ]");
            printf(" %s.%s\n\n", test_info.test_case_name(), test_info.name());
        }
        else if (showSuccesses && !test_info.result()->Failed())
        {
            eventListener->OnTestEnd(test_info);
        }
    }

    virtual void
    OnTestCaseEnd(const testing::TestCase& test_case)
    {
        if (showTestCases)
        {
            eventListener->OnTestCaseEnd(test_case);
        }
    }

    virtual void
    OnEnvironmentsTearDownStart(const testing::UnitTest& unit_test)
    {
        if (showEnvironment)
        {
            eventListener->OnEnvironmentsTearDownStart(unit_test);
        }
    }

    virtual void
    OnEnvironmentsTearDownEnd(const testing::UnitTest& unit_test)
    {
        if (showEnvironment)
        {
            eventListener->OnEnvironmentsTearDownEnd(unit_test);
        }
    }

    virtual void
    OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration)
    {
        eventListener->OnTestIterationEnd(unit_test, iteration);
    }

    virtual void
    OnTestProgramEnd(const testing::UnitTest& unit_test)
    {
        eventListener->OnTestProgramEnd(unit_test);
    }

    /**
     * Show the names of each test case.
     */
    bool showTestCases;
    /**
     * Show the names of each test.
     */
    bool showTestNames;
    /**
     * Show each success.
     */
    bool showSuccesses;
    /**
     * Show each failure as it occurs. You will also see it at the bottom after the full suite is run.
     */
    bool showInlineFailures;
    /**
     * Show the setup of the global environment.
     */
    bool showEnvironment;

protected:
    TestEventListener* eventListener;
};

ConfigurableEventListener*
registerConfigurableEventListener()
{
    // Remove the default listener
    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    auto defaultPrinter = listeners.Release(listeners.default_result_printer());

    // Add our listener, by default everything is off, like:
    // [==========] Running 149 tests from 53 test cases.
    // [==========] 149 tests from 53 test cases ran. (1 ms total)
    // [ PASSED ] 149 tests.
    ConfigurableEventListener* listener = new ConfigurableEventListener(defaultPrinter);
    listeners.Append(listener);

    return listener;
}

}

#endif // UNITTEST_CONFIGURABLE_EVENT_LISTENER_H