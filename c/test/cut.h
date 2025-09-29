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
    char * name;
    int total_successful;
    int total_failed;
};

/**
 * Definition of a test, with the test function to be called.
 */
struct cut_test_t {
    char * name;
    void (*test)(struct cut_run_t *);
};

/**
 * Configuration of cut test summary print.
 */
struct cut_config_t {
    bool print_summary;
};

/**
 * Register a unit test function to be run by cut.
 */
const void register_test(const void (*f)(struct cut_run_t *), const char * name);

/**
 * Run all unit tests registered with cut.
 */
const int run_tests(const struct cut_config_t * config);

/**
 * Assert a state within a unit test registered with cut.
 */
const void assert_true(const bool assertion, struct cut_run_t * run);

/* end: interpret as c */
#ifdef __cplusplus
}
#endif

/* end: cut header single inclusion */
#endif
