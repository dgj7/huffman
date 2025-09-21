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
typedef struct {
    char * name;
    int total_successful;
    int total_failed;
} cut_run_t;

/**
 * Definition of a test, with the test function to be called.
 */
typedef struct {
    char * name;
    void (*test)(cut_run_t *);
} cut_test_t;

/**
 * Configuration of cut test summary print.
 */
typedef struct {
    bool print_summary;
} cut_config_t;

/**
 * Register a unit test function to be run by cut.
 */
void register_test(void (*f)(cut_run_t *), char * name);

/**
 * Run all unit tests registered with cut.
 */
int run_tests(cut_config_t * config);

/**
 * Assert a state within a unit test registered with cut.
 */
void assert_true(bool assertion, cut_run_t * run);

/* end: interpret as c */
#ifdef __cplusplus
}
#endif

/* end: cut header single inclusion */
#endif
