#include <stdio.h>

#include "cut.h"
#include "test_create_tree.h"

int main() {
    /* configure cut */
    struct cut_config_t config = {.print_summary = true};

    /* register tests */
    register_test(short_string, "short_string");

    /* return the number of failed tests */
    return run_tests(&config);
}
