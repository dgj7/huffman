#ifndef C__UNIT__TESTS__H__
#define C__UNIT__TESTS__H__

/* interpret as c */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>                                            // bool data type

/**
 * A single run of a single test.
 */
struct cut_run_t {
    const char * name;
    int total_successful;
    int total_failed;
};

/**
 * Definition of a test, with the test function to be called.
 */
struct cut_test_t {
    const char * name;
    void (*test)(struct cut_run_t *);
};

/**
 * Configuration of cut test summary print.
 */
struct cut_config_t {
    const bool print_summary;
};

/**
 * Register a unit test function to be run by cut.
 */
const void register_test(void (*f)(struct cut_run_t *), const char * const name);

/**
 * Run all unit tests registered with cut.
 */
const int run_tests(const struct cut_config_t * const config);

/**
 * Assert a state within a unit test registered with cut.
 */
const void assert_true(const bool assertion, struct cut_run_t * const run);

/**
 * Assert equality for integers.
 */
const void assert_equals(const int expected, const int actual, struct cut_run_t * const run);

/* end: interpret as c */
#ifdef __cplusplus
}
#endif

/* end: cut header single inclusion */
#endif
