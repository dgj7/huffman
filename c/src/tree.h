#ifndef TREE__DG__H__
#define TREE__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


struct node_t * to_tree(struct frequency_t * frequency);

int tree_size(struct node_t * root);       // exposed for unit tests
int leaf_count(struct node_t * root);      // exposed for unit tests


#ifdef __cplusplus
}
#endif

#endif
