#ifndef TREE__DG__H__
#define TREE__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


node_t * to_tree(frequency_t * frequency);

/* functions exposed for unit tests */
int tree_size(node_t * root);
int leaf_count(node_t * root);


#ifdef __cplusplus
}
#endif

#endif
