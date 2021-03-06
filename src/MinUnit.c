#include <MinUnit.h>

#ifndef MINUNIT_MAX_TESTS
#warning No maximum number of tests defined, defaulting to 100
#define MINUNIT_MAX_TESTS 100
#endif


void (*minunitTestsTable[MINUNIT_MAX_TESTS])(minunitState *testResults);
int minunitTestCount = 0;

minunitState minunitTestState;

void minunitAddTest(void (*autoreg_func)(minunitState *testResults))
{
    if(minunitTestCount < MINUNIT_MAX_TESTS-1)
    {
        minunitTestsTable[minunitTestCount] = autoreg_func;
        minunitTestCount++;
    }
}

int minunitRun(void)
{
    minunitTestState.executed = 0;
    minunitTestState.failures = 0;
    minunitTestState.checks = 0;
    for(int i = 0; i < minunitTestCount; i++)
    {
        minunitTestState.flagFailed = 0;
        minunitTestsTable[i](&minunitTestState);
        if(minunitTestState.flagFailed != 0)
        {
            minunitTestState.failures++;
        }
        minunitTestState.executed++;
        #ifndef MINUNIT_REPORT_DISABLE
        minunitReport("\n");
        #endif
    }
    return 0;
}


#pragma GCC diagnostic ignored "-Wunused-parameter"

__attribute__((weak)) void minunitReport(const char * message)
{
    // empty body, as this is a weak function, no action should be taken
}