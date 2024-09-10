#include <stddef.h> // size_t
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit(), qsort()

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

const int ERROR_MALLOC_HUFFMAN_T = 300;
const int ERROR_MALLOC_LIST_CREATE = 301;
const int ERROR_MALLOC_LIST_RESIZE = 302;
const int ERROR_MALLOC_NODE_T = 303;
const int ERROR_INVALID_NODE_STATE = 304;

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
	sort_list(list, list_size);

	/* shrink the list until it has only one element remaining */
	while (list_size > 1) {
		/* merge the first and second elements of the list */
		node_t * left = &list[0];
		node_t * right = &list[1];
		node_t * merged = merge_nodes(left, right);

		/* update the list with one fewer elements */
		node_t * temp_list = malloc((list_size - 1) * sizeof(node_t));
		if (temp_list == NULL) {
			printf("ERROR: %d: can't allocate memory for list resize", ERROR_MALLOC_LIST_RESIZE);
			exit(ERROR_MALLOC_LIST_RESIZE);
		}

		/* swap lists */
		for (int c = 0; c < list_size -2; c++) {
			temp_list[c] = list[c+2];
		}
		free(list);
		list = temp_list;

		/* add the merged element on the end */
		list[list_size-2] = *merged;

		/* sort the list, and adjust it's size */
		sort_list(list, list_size);
		list_size--;
	}

	/* assign single element to tree struct */
	tree->root = &list[0];

	/* debug only */
	//printf("tree->root->frequency=[%d]\n", tree->root->frequency);

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
		frequency_pair_t * pair = &pairs[c];
		node_t node = (node_t) { .frequency = pair->frequency, .symbol = pair->symbol, .nt = LEAF };
		list[c] = node;
	}

	return list;
}

void sort_list(node_t * list, long length) {
	// todo
}

node_t * merge_nodes(node_t * left, node_t * right) {
	/* check for invalid states */
	if (left == NULL || right == NULL) {
		printf("ERROR: %d: invalid node state: NULL", ERROR_INVALID_NODE_STATE);
		exit(ERROR_INVALID_NODE_STATE);
	}

	/* allocate memory for the newly merged node */
	node_t * parent = malloc(sizeof(node_t));
	if (parent == NULL) {
		printf("ERROR: %d: can't allocate memory for node_t", ERROR_MALLOC_NODE_T);
		exit(ERROR_MALLOC_NODE_T);
	}

	/* assign fields to the new node */
	long frequency = left->frequency + right->frequency;
	parent->frequency = frequency;
	parent->left = left;
	parent->right = right;
	parent->nt = INTERNAL;

	/* done */
	return parent;
}
