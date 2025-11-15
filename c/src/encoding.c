#include <stdbool.h>	// bool
#include <stdio.h>		// printf()
#include <stdlib.h>		// malloc(), exit()

#include "huffman.h"
#include "encoding.h"
#include "tree.h"		// tree_size()

static const int ERROR_MALLOC_BITVEC = 400;
static const int ERROR_MALLOC_BIT_ARRAY = 401;
static const int ERROR_MALLOC_ENCODING_ROOT = 402;
static const int ERROR_MISCOUNT = 403;
static const int ERROR_MALLOC_ENCODING_NEXT = 404;
static const int ERROR_MALLOC_ENCODING_LIST = 405;

static const void make_encodings_helper_recursive(const struct node_t * const node, struct encoding_list_t * const list, bool bits[], const bool next, const short index);
static const void populate_encoding(struct encoding_t * const encoding, const struct node_t * const node, const bool bits[], const int length);

const struct encoding_list_t * const
make_encodings_helper(
	const struct node_t * const tree
	,const int length
){
	/* handle bad input */
	if (tree == NULL)
	{
		return NULL;
	}

	/* handle empty input */
	if (tree_size(tree) == 0)
	{
		return NULL;
	}

	/* allocate memory */
	struct encoding_list_t * const list = malloc(sizeof(struct encoding_list_t));
	if (list == NULL)
	{
		printf("ERROR: %d: can't allocate memory for encoding_list_t\n", ERROR_MALLOC_ENCODING_LIST);
		exit(ERROR_MALLOC_ENCODING_LIST);
	}

	/* zero out pointer, for gcc */
	list->head = NULL;

	/* create temporary, copyable array of bits to pass */
	bool bits[256];

	/* populate list */
	make_encodings_helper_recursive(tree->left, list, bits, LEFT, 0);
	make_encodings_helper_recursive(tree->right, list, bits, RIGHT, 0);

	/* done */
	return list;
}

const int
count_encodings(
	const struct encoding_list_t * list
){
	if (list == NULL)
	{
		return 0;
	}
	
	if (list->head == NULL)
	{
		return 0;
	}

	struct encoding_t * iterator = list->head;

	int count = 0;
	while (iterator != NULL)
	{
		count++;
		iterator = iterator->next;
	}

	return count;
}

static
const void
make_encodings_helper_recursive(
	const struct node_t * const node
	,struct encoding_list_t * const list
	,bool bits[]
	,const bool next
	,const short index_bits
){
	/* sc if this node is null; this'll happen if the previous call handled a leaf node */
	if (node == NULL)
	{
		return;
	}

	/* set the next element in the temporary bit array */
	bits[index_bits] = next;

	/* if leaf node, we need to do some processing */
	if (node->nt == LEAF)
	{
		/* update the linked list; if it's the first element, initialize head; otherwise, add `next` */
		if (list->head == NULL)
		{
			/* allocate memory for root */
			list->head = malloc(sizeof(struct encoding_t));
			if (list->head == NULL)
			{
				printf("ERROR: %d: can't allocate memory for encoding_t root\n", ERROR_MALLOC_ENCODING_ROOT);
				exit(ERROR_MALLOC_ENCODING_ROOT);
			}

			/* zero out pointer, for gcc */
			list->head->next = NULL;

			/* populate the root element */
			populate_encoding(list->head, node, bits, index_bits+1);
		}
		else
		{
			/* find the last element in the list */
			struct encoding_t * previous = list->head;
			while (previous->next != NULL)
			{
				previous = previous->next;
			}

			/* expect `next` is null here */
			if (previous->next != NULL)
			{
				printf("ERROR: %d: miscount to end of list", ERROR_MISCOUNT);
				exit(ERROR_MISCOUNT);
			}

			/* allocate memory for the next new element */
			previous->next = malloc(sizeof(struct encoding_t));
			if (previous->next == NULL)
			{
				printf("ERROR: %d: can't allocate memory for encoding_t->next", ERROR_MALLOC_ENCODING_NEXT);
				exit(ERROR_MALLOC_ENCODING_NEXT);
			}

			/* zero out pointer, for gcc */
			previous->next->next = NULL;

			/* populate the next element */
			populate_encoding(previous->next, node, bits, index_bits+1);
		}
	}

	/* continue traversing down the left and right child nodes */
	make_encodings_helper_recursive(node->left, list, bits, LEFT, index_bits + 1);
	make_encodings_helper_recursive(node->right, list, bits, RIGHT, index_bits + 1);
}

static
const void
populate_encoding(
	struct encoding_t * const encoding
	,const struct node_t * const node
	,const bool bits[]
	,const int length_bits
){
	/* write the symbol */
	encoding->symbol = node->symbol;

	/* get memory for the bit vector struct */
	encoding->bitvec = malloc(sizeof(struct bitvec_t));
	if (encoding->bitvec == NULL)
	{
		printf("ERROR: %d: can't allocate memory for bitvec_t", ERROR_MALLOC_BITVEC);
		exit(ERROR_MALLOC_BITVEC);
	}

	/* get memory for the bit array */
	encoding->bitvec->bits = malloc(length_bits * sizeof(bool));
	if (encoding->bitvec->bits == NULL)
	{
		printf("ERROR: %d: can't allocate memory for bitvec_t->bool[]\n", ERROR_MALLOC_BIT_ARRAY);
		exit(ERROR_MALLOC_BIT_ARRAY);
	}

	/* copy bits */
	encoding->bitvec->length = length_bits;
	for (int c = 0; c < length_bits; c++)
	{
		encoding->bitvec->bits[c] = bits[c];
	}
}
