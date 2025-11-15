#include <stdio.h>          // printf()
#include <stdlib.h>         // exit()
#include <string.h>         // strlen()

#include "huffman.h"
#include "tree.h"
#include "transform.h"
#include "encoding.h"
#include "frequency.h"

static const int ERROR_NO_SYMBOL_MATCH = 600;
static const int ERROR_MALLOC_BITS = 601;
static const int ERROR_MALLOC_ENCODED_MESSAGE_T = 602;
static const int ERROR_MALLOC_DECODED_STRING = 603;
static const int ERROR_INTERNAL_RIGHT_NODE_NULL = 604;
static const int ERROR_INTERNAL_LEFT_NODE_NULL = 605;

static const struct encoding_t * const find_encoding_by_symbol(const struct encoding_list_t * const list, const char symbol_key);
static const struct decoded_byte_t next_decoded(const struct encoded_message_t * const encoded, const struct node_t * const tree, int index);

struct decoded_byte_t {
	char byte;
	int bits;
};

const struct encoded_message_t * const
encode(
	const char * const message
	,const struct encoding_list_t * const list
){
	/* determine the length of the outgoing encoded bit array */
	int out_len = 0;
	for (int msg_idx = 0; msg_idx < strlen(message); msg_idx++) {
		const char symbol_key = message[msg_idx];
		const struct encoding_t * const encoding = find_encoding_by_symbol(list, symbol_key);
		out_len = out_len + encoding->bitvec->length;
	}

	/* allocate memory for encoded message struct */
	struct encoded_message_t * const em = malloc(sizeof(struct encoded_message_t));
	if (em == NULL) {
		printf("ERROR: %d: can't allocate memory for encoded_message_t", ERROR_MALLOC_ENCODED_MESSAGE_T);
		exit(ERROR_MALLOC_ENCODED_MESSAGE_T);
	}

	/* set the output length */
	em->length = out_len;

	/* allocate memory for the output array */
	em->bits = malloc(out_len * sizeof(bool));
	if (em->bits == NULL) {
		printf("ERROR: %d: can't allocate memory for printable encoded message string\n", ERROR_MALLOC_BITS);
		exit(ERROR_MALLOC_BITS);
	}

	/* find and append the matching bits to the output array */
	int out_idx = 0;
	for (int msg_idx = 0; msg_idx < strlen(message); msg_idx++) {
		const char symbol_key = message[msg_idx];
		const struct encoding_t * const encoding = find_encoding_by_symbol(list, symbol_key);
		for (int bit_idx = 0; bit_idx < encoding->bitvec->length; bit_idx++) {
			em->bits[out_idx] = encoding->bitvec->bits[bit_idx] ? true : false;
			out_idx++;
		}
	}

	/* done */
	return em;
}

// todo: we should be able to do this without the 'length' attribute; this is kind of like cheating
const char * const
decode(
	const struct encoded_message_t * const encoded
	,const struct node_t * const tree
	,const int msg_len
){
	/* allocate memory for the output string */
	char * const output = malloc((msg_len + 1) * sizeof(char));
	if (output == NULL)
	{
		printf("ERROR: %d: can't allocate memory for decoded string\n", ERROR_MALLOC_DECODED_STRING);
		exit(ERROR_MALLOC_DECODED_STRING);
	}

	/* null terminate */
	output[msg_len] = '\0';

	/* loop over bits to find decoded bytes */
	int consumed = 0;
	int out_str_idx = 0;
	while (consumed < (encoded->length))
	{
		struct decoded_byte_t next = next_decoded(encoded, tree, consumed);
		consumed = consumed + next.bits;
		output[out_str_idx] = next.byte;
		out_str_idx += 1;
	}
	return output;
}

static
const struct encoding_t * const
find_encoding_by_symbol(
	const struct encoding_list_t * const list
	,const char symbol_key
){
	/* loop over to find match */
	const struct encoding_t * encoding = list->head;
	while (encoding->next != NULL) {
		if (encoding->symbol == symbol_key) {
			break;
		}
		encoding = encoding->next;
	}

	/* error if no match is found */
	if (encoding->symbol != symbol_key) {
		printf("ERROR: %d: can't find match for symbol [%c]\n", ERROR_NO_SYMBOL_MATCH, symbol_key);
		exit(ERROR_NO_SYMBOL_MATCH);
	}

	/* done */
	return encoding;
}

static
const struct decoded_byte_t
next_decoded(
	const struct encoded_message_t * const encoded
	,const struct node_t * const tree
	,int index
){
	struct node_t * node = (struct node_t *) tree;
	int consumed = 0;
	for (int x = index; x < encoded->length; x++)
	{
		if (node->nt == LEAF)
		{
			break;
		}
		else
		{
			/* get the current bit */
			const bool bit = encoded->bits[x];
			//printf("[%c]->%c[%c(%lu)]\n", bit ? '1' : '0', node->nt == 98 ? 'I' : 'L', node->symbol, node->frequency);

			/* use the current bit to reassign the node pointer */
			if (bit)
			{
				if (node->right == NULL)
				{
					printf("ERROR: %d: node->right of INTERNAL node is null!\n", ERROR_INTERNAL_RIGHT_NODE_NULL);
					exit(ERROR_INTERNAL_RIGHT_NODE_NULL);
				}
				node = node->right;
			}
			else
			{
				if (node->left == NULL)
				{
					printf("ERROR: %d: node->left of INTERNAL node is null!\n", ERROR_INTERNAL_LEFT_NODE_NULL);
					exit(ERROR_INTERNAL_LEFT_NODE_NULL);
				}
				node = node->left;
			}

			/* increment the number of bits consumed */
			consumed++;
		}
	}

	return (struct decoded_byte_t) { .byte=node->symbol, .bits=consumed };
}
