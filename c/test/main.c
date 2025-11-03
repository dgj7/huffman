#include <stdio.h>

#include "cut.h"
#include "end_to_end_tests.h"

int main() {
    /* configure cut */
    struct cut_config_t config = {.print_summary = true};

    /* register tests */
    register_test(empty_string, "empty_string");
    register_test(single_byte, "single_byte");
    register_test(short_string, "short_string");
    register_test(main_case, "main_case");

    /* return the number of failed tests */
    return run_tests(&config);
}
