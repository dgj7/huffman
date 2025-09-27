#include "cut.h"
#include "test_create_tree.h"

#include <stddef.h>

#include "frequency.h"
#include "huffman.h"
#include "tree.h"

void short_string(cut_run_t * run)
{
    node_t * tree = create_tree("f", 1);

    assert_true(1 == tree_size(tree), run);
    assert_true(1 == leaf_count(tree), run);
}
