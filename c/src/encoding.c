#include <stdbool.h>	// bool
#include <stdio.h>		// printf()
#include <stdlib.h>		// malloc(), exit()

#include "huffman.h"
#include "encoding.h"

static const int ERROR_MALLOC_BITVEC = 400;
static const int ERROR_MALLOC_BIT_ARRAY = 401;
static const int ERROR_MALLOC_ENCODING_ROOT = 402;
static const int ERROR_MISCOUNT = 403;
static const int ERROR_MALLOC_ENCODING_NEXT = 404;
static const int ERROR_MALLOC_ENCODING_LIST = 405;

static void make_encodings_helper_recursive(struct node_t * node, struct encoding_list_t * list, bool bits[], bool next, short index);
static void populate_encoding(struct encoding_t * encoding, struct node_t * node, bool bits[], int length);

struct encoding_list_t *
make_encodings_helper(
	struct node_t * tree
	,int length
){
	/* handle bad input */
	if (tree == NULL)
	{
		return NULL;
	}

	/* allocate memory */
	struct encoding_list_t * list = malloc(sizeof(struct encoding_list_t));
	if (list == NULL)
	{
		printf("ERROR: %d: can't allocate memory for encoding_list_t\n", ERROR_MALLOC_ENCODING_LIST);
		exit(ERROR_MALLOC_ENCODING_LIST);
	}

	/* zero out pointer, for gcc */
	list->head = NULL;

	/* create temporary, copyable array of bits to pass */
	bool bits[256];

	/* call for both child nodes */
	make_encodings_helper_recursive(tree->left, list, bits, LEFT, 0);
	make_encodings_helper_recursive(tree->right, list, bits, RIGHT, 0);

	/* done */
	return list;
}

static
void
make_encodings_helper_recursive(
	struct node_t * node
	,struct encoding_list_t * list
	,bool bits[]
	,bool next
	,short index_bits
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
void
populate_encoding(
	struct encoding_t * encoding
	,struct node_t * node
	,bool bits[]
	,int length_bits
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
