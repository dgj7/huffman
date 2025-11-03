#ifndef TREE__DG__H__
#define TREE__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "frequency.h"

const struct node_t * const to_tree(const struct frequency_t * const frequency);

const int tree_size(const struct node_t * const root);       // exposed for unit tests
const int leaf_count(const struct node_t * const root);      // exposed for unit tests


#ifdef __cplusplus
}
#endif

#endif
