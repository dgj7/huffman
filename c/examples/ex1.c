#include <stdio.h> 			// printf()
#include <string.h> 		// strcpy(), strlen(), strncat()
#include <stdlib.h> 		// malloc(), free()
#include <time.h> 			// clock_t, CLOCKS_PER_SEC
#include <stdlib.h> 		// exit()

#include "huffman.h"		// huffman library

const int IDX_ARG = 1;
const int IDX_MESSAGE = 2;

const int ERROR_READ = 1;
const int ERROR_UNKNOWN_ARG = 2;
const int ERROR_UNKNOWN_ARG_COUNT = 3;
const int ERROR_NO_SYMBOL_MATCH = 4;
const int ERROR_MALLOC_BITS = 5;
const int ERROR_MALLOC_ENCODED_MESSAGE_T = 6;
const int ERROR_MALLOC_PRINTABLE_MESSAGE = 7;
const int ERROR_MALLOC_DECODED_STRING = 8;
const int ERROR_INTERNAL_RIGHT_NODE_NULL = 9;
const int ERROR_INTERNAL_LEFT_NODE_NULL = 10;


struct encoded_message_t {
	bool * bits;
	int length;
};

struct encoded_message_t * encode(char * message, struct encoding_list_t * list);
char * printable_encoded_message(struct encoded_message_t * em);
char * decode(struct encoded_message_t * encoded, struct node_t * tree, int msg_len);

struct encoding_t * find_encoding_by_symbol(struct encoding_list_t * list, char symbol_key);

int main(int argc, char **argv) {
	clock_t start = clock();

	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			size_t length = strlen(argv[IDX_MESSAGE]);
			char *message = malloc(length);
			if (message) {
				/* copy the message into somewhere it's usable */
				strcpy(message, argv[IDX_MESSAGE]);

				/* create huffman-related data structures */
				struct node_t * tree = create_tree(message, length);
				struct encoding_list_t * encodings = extract_encodings(tree);

				/* do transformations with the huffman data */
				struct encoded_message_t * encoded = encode(message, encodings);
				char *printable = printable_encoded_message(encoded);
				char *decoded = decode(encoded, tree, length);

				/* print results */
				printf("input:   [%s]\n", message);
				printf("encoded: [%s]\n", printable);
				printf("decoded: [%s]\n", decoded);

				/* free memory */
				free_tree(tree);
				free_encodings(encodings);
			} else {
				printf("ERROR: can't read message: %s", argv[IDX_MESSAGE]);
				return ERROR_READ;
			}
		} else {
			printf("ERROR: unknown arg: %s\n", argv[IDX_ARG]);
			return ERROR_UNKNOWN_ARG;
		}
	} else {
		printf("Error: unknown arg count: %d\n", argc);
		return ERROR_UNKNOWN_ARG_COUNT;
	}

	/* declare success, print profiling info */
	clock_t elapsed = clock() - start;
	double ms = (((double)elapsed)/CLOCKS_PER_SEC)/1000;
	printf("done. (%.0lf ms)\n", ms);

	/* done */
	return 0;
}

struct encoded_message_t * encode(char * message, struct encoding_list_t * list) {
	/* determine the length of the outgoing encoded bit array */
	int out_len = 0;
	for (int msg_idx = 0; msg_idx < strlen(message); msg_idx++) {
		char symbol_key = message[msg_idx];
		struct encoding_t * encoding = find_encoding_by_symbol(list, symbol_key);
		out_len = out_len + encoding->bitvec->length;
	}

	/* allocate memory for encoded message struct */
	struct encoded_message_t * em = malloc(sizeof(struct encoded_message_t));
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
		char symbol_key = message[msg_idx];
		struct encoding_t * encoding = find_encoding_by_symbol(list, symbol_key);
		for (int bit_idx = 0; bit_idx < encoding->bitvec->length; bit_idx++) {
			em->bits[out_idx] = encoding->bitvec->bits[bit_idx] ? true : false;
			out_idx++;
		}
	}

	/* todo */
	return em;
}

char * printable_encoded_message(struct encoded_message_t * em) {
	/* allocate memory for output string */
	char * output = malloc(em->length * sizeof(char));
	if (output == NULL) {
		printf("ERROR: %d: can't allocate memory for printable encoded message", ERROR_MALLOC_PRINTABLE_MESSAGE);
		exit(ERROR_MALLOC_PRINTABLE_MESSAGE);
	}

	/* copy bits */
	for (int idx = 0; idx < em->length; idx++) {
		output[idx] = em->bits[idx] ? '1' : '0';
	}

	/* done */
	return output;
}

char * decode(struct encoded_message_t * encoded, struct node_t * tree, int msg_len) {
	/* store current output string index */
	int out_str_idx = 0;

	/* allocate memory for the output string */
	char * output = malloc(msg_len * sizeof(char));
	if (output == NULL) {
		printf("ERROR: %d: can't allocate memory for decoded string\n", ERROR_MALLOC_DECODED_STRING);
		exit(ERROR_MALLOC_DECODED_STRING);
	}

	/* loop over bits */
	struct node_t * node = tree;
	for (int bit_idx = 0; bit_idx < encoded->length; bit_idx++) {
		/* if it's a leaf node, we can grab the symbol and put it on the output string */
		if (node->nt == LEAF) {
			output[out_str_idx] = node->symbol;
			out_str_idx++;
			node = tree;
		}

		/* get the current bit */
		bool bit = encoded->bits[bit_idx];

		/* use the current bit to reassign the node pointer */
		if (bit) {
			if (node->right == NULL) {
				printf("ERROR: %d: node->right of INTERNAL node is null!", ERROR_INTERNAL_RIGHT_NODE_NULL);
				exit(ERROR_INTERNAL_RIGHT_NODE_NULL);
			}
			node = node->right;
		} else {
			if (node->left == NULL) {
				printf("ERROR: %d: node->left of INTERNAL node is null!", ERROR_INTERNAL_LEFT_NODE_NULL);
				exit(ERROR_INTERNAL_LEFT_NODE_NULL);
			}
			node = node->left;
		}
	}

	/* done */
	return output;
}

struct encoding_t * find_encoding_by_symbol(struct encoding_list_t * list, char symbol_key) {
	/* loop over to find match */
	struct encoding_t * encoding = list->head;
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
