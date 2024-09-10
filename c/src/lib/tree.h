#ifndef __TREE__DG__H__
#define __TREE__DG__H__

huffman_t * to_tree(frequency_t * frequency);

node_t * to_list(frequency_pair_t * pairs, long length);
void sort_list(node_t * list);
node_t * merge_nodes(node_t * left, node_t * right);
void update_list(node_t * list, node_t * element);

#endif
