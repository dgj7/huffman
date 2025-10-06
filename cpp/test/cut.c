#include <stdio.h>          // printf()
#include <string.h>         // strcpy()
#include <stdlib.h>         // malloc()

#include "cut.h"

#define CUT_VERSION "0.0.14"
#define MAX_TESTS 1000

struct cut_test_t tests[MAX_TESTS];
static int cutTestIndex = 0;

const static int ERROR_MALLOC_TEST_NAME = 101;
const static int ERROR_MALLOC_RUN_NAME = 102;

/**
 * Register a test with cut; this is necessary for the test to be run by the framework.
 */
const void
register_test(
    const void (*f)(struct cut_run_t *)
    ,const char * const name
){
    /* create a test instance; this will be stored internally */
    struct cut_test_t test;

    /* set test function */
    test.test = f;

    /* set test name */
    test.name = (char*) malloc(sizeof(char) * strlen(name));
    if (test.name == NULL) {
        printf("ERROR: %d: failed to allocate memory for test name\n", ERROR_MALLOC_TEST_NAME);
        exit(1);
    }
    strcpy((char*)test.name, name);

    /* store the test */
    tests[cutTestIndex] = test;

    /* increment the current index */
    cutTestIndex += 1;
}

/**
 * Run all tests registered with cut.
 */
const int
run_tests(
    const struct cut_config_t * const config
){
    /* storage for the number of failed tests; initially, zero */
    int failed = 0;
    int succeeded = 0;
    int test_function_count = 0;

    /* store run information */
    struct cut_run_t runs[MAX_TESTS];

    /* loop over all registered tests; number is equal to the current index, minus 1 */
    for (int c = 0; c < cutTestIndex; c++)
    {
        /* create a test run; values are initially zero */
        struct cut_run_t run = {0, 0};

        /* get the test instance */
        struct cut_test_t test = tests[c];

        /* copy the test name over */
        run.name = (char*) malloc(sizeof(strlen(test.name)));
        if (run.name == NULL) {
            printf("ERROR: %d: failed to allocate memory for ru n name\n", ERROR_MALLOC_RUN_NAME);
            exit(ERROR_MALLOC_RUN_NAME);
        }
        strcpy((char*)run.name, test.name);

        /* run the test instance */
        (*test.test)(&run);

        /* update total counts */
        failed += run.total_failed > 0 ? 1 : 0;
        succeeded += run.total_failed < 1 ? 1 : 0;
        test_function_count++;

        /* store the run for printing later */
        runs[c] = run;
    }

    /* print end summary, if requested */
    if (config->print_summary)
    {
        printf("\033[35munit test summary - cut v%s\033[m\n", CUT_VERSION);
        for (int c = 0; c < test_function_count; c++)
        {
            struct cut_run_t run = runs[c];
            printf("\t%s: %s (%d ok, %d failed)\n", run.name, run.total_failed > 0 ? "\033[31mfailed\033[m" : "\033[32mok\033[m", run.total_successful, run.total_failed);
        }
        printf("%s: %d succeeded, %d failed\n", failed > 0 ? "\033[31mFAIL\033[m" : "\033[32mSUCCESS\033[m", succeeded, failed);
    }

    /* done; return the failed count */
    return failed;
}

/**
 * Assert that the given value is true.
 */
const void
assert_true(
    const bool assertion
    ,struct cut_run_t * const run
){
    if (assertion)
    {
        run->total_successful += 1;
    } else {
        run->total_failed += 1;
    }
}
