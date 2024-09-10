#include <stddef.h> // size_t
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit()

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

const int ERROR_MALLOC_HUFFMAN_T = 300;
const int ERROR_MALLOC_LIST_CREATE = 301;

huffman_t * to_tree(frequency_t * frequency) {
	/* allocate space for the new tree */
	huffman_t * tree = malloc(sizeof(huffman_t));
	if (tree == NULL) {
		printf("ERROR: %d: can't allocate memory for huffman_t", ERROR_MALLOC_HUFFMAN_T);
		exit(ERROR_MALLOC_HUFFMAN_T);
	}

	/* create an initial list of nodes, and sort it */
	node_t * list = to_list(frequency->pairs, frequency->count);
	long list_size = frequency->count;
	sort_list(list);

	/* shrink the list until it has only one element remaining */
	while (list_size > 1) {
		node_t * left = &list[0];
		node_t * right = &list[1];
		node_t * merged = merge_nodes(left, right);
		update_list(list, merged);
		sort_list(list);
		list_size--;
	}

	/* free new allocations */
	free(list);

	/* done */
	return tree;
}

node_t * to_list(frequency_pair_t * pairs, long length) {
	node_t * list = malloc(length * sizeof(node_t));
	if (list == NULL) {
		printf("ERROR: %d: can't allocate memory for list", ERROR_MALLOC_LIST_CREATE);
		exit(ERROR_MALLOC_LIST_CREATE);
	}

	for (int c = 0; c < length; c++) {
		// todo
	}

	return list;
}

void sort_list(node_t * list) {
	// todo
}

node_t * merge_nodes(node_t * left, node_t * right) {
	// todo
	return NULL;
}

void update_list(node_t * list, node_t * element) {
	// todo
}
