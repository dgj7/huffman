#include "cut.h"
#include "test_create_tree.h"

#include <stddef.h>

#include "frequency.h"
#include "huffman.h"
#include "tree.h"
#include "encoding.h"           // count_encodings()

void empty_string(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("", 0);

    assert_true(0 == tree_size(tree), run);
    assert_true(0 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(0 == count_encodings(encodings), run);

    // todo: need to do test rest of the calls in these tests
    // todo: rename this file to end_to_end
}

void single_byte(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("f", 1);

    assert_true(1 == tree_size(tree), run);
    assert_true(1 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(1 == count_encodings(encodings), run);
}

void short_string(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("abcaba", 6);

    assert_true(5 == tree_size(tree), run);
    assert_true(3 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(3 == count_encodings(encodings), run);
}

void main_case(struct cut_run_t * run)
{
    const struct node_t * tree = create_tree("this is a sample input string. its text is being used to test the huffman coding tree.", 86);

    assert_true(41 == tree_size(tree), run);
    assert_true(21 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(21 == count_encodings(encodings), run);
}
