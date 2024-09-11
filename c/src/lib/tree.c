#include <stddef.h> // size_t
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit(), qsort()
#include <stdbool.h> // bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

const int ERROR_MALLOC_HUFFMAN_T = 300;
const int ERROR_MALLOC_LIST_CREATE = 301;
const int ERROR_MALLOC_LIST_RESIZE = 302;
const int ERROR_MALLOC_NODE_T = 303;
const int ERROR_INVALID_NODE_STATE = 304;

const int COMPARE_LESS = -1;
const int COMPARE_EQUAL = 0;
const int COMPARE_GREATER = 1;

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
	//debug_print_tree(tree->root);

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

void sort_list(node_t * list, long length) {
	// todo
	//qsort(list, length, sizeof(node_t), compare);
}

/**
 * Compare function, intended for node_t.
 * 
 * This function should:
 * 1) return NEGATIVE if: left < right
 * 2) return ZERO if: left == right
 * 3) return POSITIVE if: left > right
 * 
 * This function will compare by checking three fields, in order of importance/priority:
 * 1) frequency
 * 2) symbol
 * 3) tree size (total node count)
 * 
 * see also: https://www.gnu.org/software/libc/manual/html_node/Comparison-Functions.html
 * see also: https://github.com/dgj7/huffman/blob/main/.docs/algorithm.md
 */
int compare(const void *_left, const void *_right) {
	const node_t left = *((node_t *) _left);
	const node_t right = *((node_t *) _right);

	int compare_freq = (left.frequency == right.frequency ? COMPARE_EQUAL : (left.frequency < right.frequency ? COMPARE_LESS : COMPARE_GREATER));
	int compare_symbol = (left.symbol == right.symbol ? COMPARE_EQUAL : (left.symbol < right.symbol ? COMPARE_LESS : COMPARE_GREATER));
	bool both_leaves = left.nt == LEAF && right.nt == LEAF;

	if (compare_freq == COMPARE_EQUAL) {
		if (both_leaves) {
			return compare_symbol;
		} else {
			int left_size = tree_size((node_t *)_left);
			int right_size = tree_size((node_t *)_right);

			return left_size == right_size ? COMPARE_EQUAL : (left_size < right_size ? COMPARE_LESS : COMPARE_GREATER);
		}
	} else {
		return compare_freq;
	}
}

int tree_size(node_t * root) {
	int left_size = root->left == NULL ? 0 : tree_size(root->left);
	int right_size = root->right== NULL ? 0 : tree_size(root->right);
	return left_size + right_size + 1;
}

void debug_print_tree(node_t * root) {
	if (root == NULL) {
		printf("ROOT NULL");
	} else if (root->nt == INTERNAL) {
		printf("INTERNAL: frequency=[%d]\n", root->frequency);
		debug_print_tree(root->left);
		debug_print_tree(root->right);
	} else {
		printf("LEAF: frequency=[%d], symbol=[%c]\n", root->frequency, root->symbol);
	}
}
