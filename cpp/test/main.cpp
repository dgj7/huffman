#include <stdio.h>

#include "cut.h"

#include "end_to_end_tests.hpp"

int
main(
    int argc
    ,char **argv
){
    /* configure cut */
    const struct cut_config_t config = {true};

    /* register the tests */
    register_test(empty_string, "empty_string");
    register_test(short_string, "short_string");
    register_test(main_case, "main_case");

    /* return the number of failed tests */
    return run_tests(&config);
}
