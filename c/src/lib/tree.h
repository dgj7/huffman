#ifndef __TREE__DG__H__
#define __TREE__DG__H__

huffman_t * to_tree(frequency_t * frequency);

node_t * to_list(frequency_pair_t * pairs, long length);
node_t * copy_node(node_t * source);
node_t * merge_nodes(node_t * left, node_t * right);
void bubble_sort(node_t * list, long length);
int compare(const void *_left, const void *_right);
int tree_size(node_t * root);

void debug_print_tree(node_t * root, char * prefix, int level);

#endif
