#include <stddef.h> // size_t
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit(), qsort()
#include <stdbool.h> // bool
#include <string.h> // strcat()

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

const int ERROR_MALLOC_HUFFMAN_T = 300;
const int ERROR_MALLOC_LIST_CREATE = 301;
const int ERROR_MALLOC_LIST_RESIZE = 302;
const int ERROR_MALLOC_NODE_T = 303;
const int ERROR_MALLOC_NODE_T_COPY = 304;
const int ERROR_INVALID_NODE_STATE = 305;

const int COMPARE_LESS = -1;
const int COMPARE_EQUAL = 0;
const int COMPARE_GREATER = 1;

static node_t * to_list(frequency_pair_t * pairs, long length);
static node_t * copy_node(node_t * source);
static node_t * merge_nodes(node_t * left, node_t * right);
static void bubble_sort(node_t * list, long length);
static int compare(const void *_left, const void *_right);
//static void debug_print_tree(node_t * root, char * prefix, int level);

node_t * to_tree(frequency_t * frequency)
{
	/* create an initial list of nodes, and sort it */
	node_t * list = to_list(frequency->pairs, frequency->count);
	long list_size = frequency->count;
	bubble_sort(list, list_size);

	/* shrink the list until it has only one element remaining */
	while (list_size > 1)
	{
		/* merge the first and second elements of the list */
		node_t * left = &list[0];
		node_t * right = &list[1];
		node_t * merged = merge_nodes(left, right);

		/* update the list with one fewer elements */
		node_t * temp_list = malloc((list_size - 1) * sizeof(node_t));
		if (temp_list == NULL)
		{
			printf("ERROR: %d: can't allocate memory for list resize", ERROR_MALLOC_LIST_RESIZE);
			exit(ERROR_MALLOC_LIST_RESIZE);
		}

		/* swap lists */
		for (int c = 0; c < list_size -2; c++)
		{
			temp_list[c] = list[c+2];
		}
		free(list);
		list = temp_list;
		list_size--;

		/* add the merged element on the end */
		const int MERGED_INDEX = list_size - 1;
		list[MERGED_INDEX] = *merged;

		/* debug only */
		//printf("to_tree(): adding merged element to list idx [%d/%d->%d]: [%s|%d|%c]\n", MERGED_INDEX, list_size+1, list_size, merged->nt == INTERNAL ? "INTERNAL" : "LEAF", merged->frequency, merged->symbol);
		//for (int c = 0; c < list_size; c++) {
			//node_t element = list[c];
			//printf("\tto_tree(): list[%d]: [%s|%d|%c]\n", c, element.nt == INTERNAL ? "INTERNAL" : "LEAF", element.frequency, element.symbol);
			//debug_print_tree(&element, "\t", 0);
		//}

		/* sort the list */
		bubble_sort(list, list_size);
	}

	/* debug only */
	//debug_print_tree(&list[0], "\t", 0);

	/* done */
	return &list[0];
}

static node_t * to_list(frequency_pair_t * pairs, long length)
{
	node_t * list = malloc(length * sizeof(node_t));
	if (list == NULL)
	{
		printf("ERROR: %d: can't allocate memory for list", ERROR_MALLOC_LIST_CREATE);
		exit(ERROR_MALLOC_LIST_CREATE);
	}

	for (int c = 0; c < length; c++)
	{
		frequency_pair_t * pair = &pairs[c];
		node_t node = (node_t) { .frequency = pair->frequency, .symbol = pair->symbol, .nt = LEAF, .tree_size = 1 };
		list[c] = node;
		//printf("to_list(): adding element to list idx [%d/%d]: [%s|%d|%c]\n", c, length, node.nt == INTERNAL ? "INTERNAL" : "LEAF", node.frequency, node.symbol);
	}

	return list;
}

static node_t * merge_nodes(node_t * left, node_t * right)
{
	/* check for invalid states */
	if (left == NULL || right == NULL)
	{
		printf("ERROR: %d: invalid node state: NULL", ERROR_INVALID_NODE_STATE);
		exit(ERROR_INVALID_NODE_STATE);
	}

	/* allocate memory for the newly merged node */
	node_t * parent = malloc(sizeof(node_t));
	if (parent == NULL)
	{
		printf("ERROR: %d: can't allocate memory for node_t", ERROR_MALLOC_NODE_T);
		exit(ERROR_MALLOC_NODE_T);
	}

	/* assign fields to the new node */
	long frequency = left->frequency + right->frequency;
	parent->frequency = frequency;
	parent->left = copy_node(left);
	parent->right = copy_node(right);
	parent->nt = INTERNAL;
	parent->tree_size = 1 + left->tree_size + right->tree_size;

	/* done */
	return parent;
}

static node_t * copy_node(node_t * source)
{
	/* no work to do if incoming node is NULL */
	if (source == NULL)
	{
		return NULL;
	}

	/* allocate memory */
	node_t * result = malloc(sizeof(node_t));
	if (result == NULL)
	{
		printf("ERROR: %d: can't allocate memory for node_t copy", ERROR_MALLOC_NODE_T_COPY);
		exit(ERROR_MALLOC_NODE_T_COPY);
	}

	/* set non-pointer fields */
	result->frequency = source->frequency;
	result->symbol = source->symbol;
	result->nt = source->nt;
	result->tree_size = source->tree_size;

	/* copy left and right child nodes */
	result->left = copy_node(source->left);
	result->right = copy_node(source->right);

	/* done */
	return result;
}

static void bubble_sort(node_t * list, long length)
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			const int LEFT_IDX = j;
			const int RIGHT_IDX = j+1;
			//printf("bubble_sort(): length=[%d], i=[%d], j=[%d], left_idx=[%d], right_idx=[%d]\n", length, i, j, LEFT_IDX, RIGHT_IDX);
			const node_t left = list[LEFT_IDX];
			const node_t right = list[RIGHT_IDX];

			if (compare(&left, &right) == COMPARE_GREATER)
			{
				//printf("\tbubble_sort(): swapping: left=[%s|%d|%c], right=[%s|%d|%c]\n", left.nt == INTERNAL ? "INTERNAL" : "LEAF", left.frequency, left.symbol, right.nt == INTERNAL ? "INTERNAL" : "LEAF", right.frequency, right.symbol);
				list[LEFT_IDX] = right;
				list[RIGHT_IDX] = left;
			}
		}
	}
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
static int compare(const void *_left, const void *_right)
{
	const node_t left = *((node_t *) _left);
	const node_t right = *((node_t *) _right);

	int compare_freq = (left.frequency == right.frequency ? COMPARE_EQUAL : (left.frequency < right.frequency ? COMPARE_LESS : COMPARE_GREATER));
	int compare_symbol = (left.symbol == right.symbol ? COMPARE_EQUAL : (left.symbol < right.symbol ? COMPARE_LESS : COMPARE_GREATER));
	bool both_leaves = left.nt == LEAF && right.nt == LEAF;

	if (compare_freq == COMPARE_EQUAL)
	{
		if (both_leaves)
		{
			return compare_symbol;
		}
		else
		{
			int left_size = tree_size((node_t *)_left);
			int right_size = tree_size((node_t *)_right);

			return left_size == right_size ? COMPARE_EQUAL : (left_size < right_size ? COMPARE_LESS : COMPARE_GREATER);
		}
	}
	else
	{
		return compare_freq;
	}
}

int tree_size(node_t * root)
{
	int left_size = root->left == NULL ? 0 : tree_size(root->left);
	int right_size = root->right == NULL ? 0 : tree_size(root->right);
	return left_size + right_size + 1;
}

int leaf_count(node_t * root)
{
	if (root == NULL)
	{
		return 0;
	}

	if (root->nt == LEAF)
	{
		return 1;
	}

	int left = leaf_count(root->left);
	int right = leaf_count(root->right);
	return left + right;
}

/*
static void debug_print_tree(node_t * root, char * prefix, int level)
{
	if (root == NULL)
	{
		printf("%sROOT NULL", prefix);
	} 
	else if (root->nt == INTERNAL)
	{
		printf("%s[LVL=%d][SZ=%d] INTERNAL: frequency=[%lu]\n", prefix, level, root->tree_size, root->frequency);
		debug_print_tree(root->left, prefix, level + 1);
		debug_print_tree(root->right, prefix, level + 1);
	}
	else
	{
		printf("%s[LVL=%d][SZ=%d] LEAF: frequency=[%lu], symbol=[%c]\n", prefix, level, root->tree_size, root->frequency, root->symbol);
	}
}
*/
