#include "cut.h"
#include "test_create_tree.h"

#include <stddef.h>

#include "frequency.h"
#include "huffman.h"
#include "tree.h"

void short_string(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("f", 1);

    assert_true(1 == tree_size(tree), run);
    assert_true(1 == leaf_count(tree), run);
}

void main_case(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("this is a sample input string. its text is being used to test the huffman coding tree.", 86);

    assert_true(41 == tree_size(tree), run);
    assert_true(21 == leaf_count(tree), run);
}
