#include <stddef.h>		// size_t
#include <stdio.h>		// printf()
#include <stdlib.h>		// malloc(), exit(), qsort()
#include <stdbool.h>	// bool
#include <string.h>		// strcat()

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

static const int ERROR_MALLOC_LIST_CREATE = 300;
static const int ERROR_MALLOC_LIST_RESIZE = 301;
static const int ERROR_MALLOC_NODE_T = 302;
static const int ERROR_MALLOC_NODE_T_COPY = 303;
static const int ERROR_INVALID_NODE_STATE = 304;

static const int COMPARE_LESS = -1;
static const int COMPARE_EQUAL = 0;
static const int COMPARE_GREATER = 1;

static struct node_t * to_list(struct frequency_pair_t * pairs, long length);
static struct node_t * copy_node(struct node_t * source);
static struct node_t * merge_nodes(struct node_t * left, struct node_t * right);
static void bubble_sort(struct node_t * list, long length);
static int compare(const void *_left, const void *_right);

struct node_t *
to_tree(
	struct frequency_t * frequency
){
	/* create an initial list of nodes, and sort it */
	struct node_t * list = to_list(frequency->pairs, frequency->count);
	long list_size = frequency->count;
	bubble_sort(list, list_size);

	/* shrink the list until it has only one element remaining */
	while (list_size > 1)
	{
		/* merge the first and second elements of the list */
		struct node_t * left = &list[0];
		struct node_t * right = &list[1];
		struct node_t * merged = merge_nodes(left, right);

		/* update the list with one fewer elements */
		struct node_t * temp_list = malloc((list_size - 1) * sizeof(struct node_t));
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

		/* sort the list */
		bubble_sort(list, list_size);
	}

	/* done */
	return &list[0];
}

static
struct node_t *
to_list(
	struct frequency_pair_t * pairs
	,long length
){
	struct node_t * list = malloc(length * sizeof(struct node_t));
	if (list == NULL)
	{
		printf("ERROR: %d: can't allocate memory for list", ERROR_MALLOC_LIST_CREATE);
		exit(ERROR_MALLOC_LIST_CREATE);
	}

	for (int c = 0; c < length; c++)
	{
		struct frequency_pair_t * pair = &pairs[c];
		struct node_t node = (struct node_t) { .frequency = pair->frequency, .symbol = pair->symbol, .nt = LEAF, .tree_size = 1 };
		list[c] = node;
	}

	return list;
}

static
struct node_t *
merge_nodes(
	struct node_t * left
	,struct node_t * right
){
	/* check for invalid states */
	if (left == NULL || right == NULL)
	{
		printf("ERROR: %d: invalid node state: NULL", ERROR_INVALID_NODE_STATE);
		exit(ERROR_INVALID_NODE_STATE);
	}

	/* allocate memory for the newly merged node */
	struct node_t * parent = malloc(sizeof(struct node_t));
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

static
struct node_t *
copy_node(
	struct node_t * source
){
	/* no work to do if incoming node is NULL */
	if (source == NULL)
	{
		return NULL;
	}

	/* allocate memory */
	struct node_t * result = malloc(sizeof(struct node_t));
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

static
void
bubble_sort(
	struct node_t * list
	,long length
){
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			const int LEFT_IDX = j;
			const int RIGHT_IDX = j+1;
			const struct node_t left = list[LEFT_IDX];
			const struct node_t right = list[RIGHT_IDX];

			if (compare(&left, &right) == COMPARE_GREATER)
			{
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
static
int
compare(
	const void *_left
	,const void *_right
){
	const struct node_t left = *((struct node_t *) _left);
	const struct node_t right = *((struct node_t *) _right);

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
			int left_size = tree_size((struct node_t *)_left);
			int right_size = tree_size((struct node_t *)_right);

			return left_size == right_size ? COMPARE_EQUAL : (left_size < right_size ? COMPARE_LESS : COMPARE_GREATER);
		}
	}
	else
	{
		return compare_freq;
	}
}

int
tree_size(
	struct node_t * root
){
	int left_size = root->left == NULL ? 0 : tree_size(root->left);
	int right_size = root->right == NULL ? 0 : tree_size(root->right);
	return left_size + right_size + 1;
}

int
leaf_count(
	struct node_t * root
){
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
