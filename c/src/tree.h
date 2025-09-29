#ifndef TREE__DG__H__
#define TREE__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


node_t * to_tree(frequency_t * frequency);

int tree_size(node_t * root);       // exposed for unit tests
int leaf_count(node_t * root);      // exposed for unit tests


#ifdef __cplusplus
}
#endif

#endif
