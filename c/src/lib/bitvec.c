#include <stdbool.h> // bool
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit()

#include "huffman.h"
#include "bitvec.h"

const int ERROR_MALLOC_BIT_ARRAY = 400;
const int ERROR_MALLOC_ENCODINGS = 401;
const int ERROR_MALLOC_BITVEC = 402;

encoding_t * make_encodings(node_t * tree) {
	/* handle bad input */
	if (tree == NULL) {
		return NULL;
	}

	/* allocate memory */
	short nodes = tree->tree_size;
	encoding_t * encodings = malloc(nodes * sizeof(encoding_t));
	if (encodings == NULL) {
		printf("ERROR: %d: can't allocate memory for encoding_t *\n", ERROR_MALLOC_ENCODINGS);
		exit(ERROR_MALLOC_ENCODINGS);
	}

	/* create temporary, copyable array of bits to pass */
	bool bits[256];

	/* call for both child nodes */
	make_encodings_recursive(tree->left, encodings, bits, 0, 0);
	make_encodings_recursive(tree->right, encodings, bits, 1, 0);

	/* done */
	return encodings;
}

void make_encodings_recursive(node_t * node, encoding_t * encodings, bool bits[], bool next, short index) {
	if (node == NULL) {
		printf("WARNING: make_encodings_recursive given null node\n");
		return;
	} else {
		bits[index] = next;
		if (node->nt == LEAF) {
			/* initialize the encoding */
			short length = index + 1;
			encoding_t encoding = { .symbol = node->symbol };

			/* get memory for the bit vector */
			encoding.bitvec.bits = malloc(length * sizeof(bool));
			if (encoding.bitvec.bits == NULL) {
				printf("ERROR: %d: can't allocate memory for bitvec_t\n", ERROR_MALLOC_BITVEC);
				exit(ERROR_MALLOC_BITVEC);
			}

			/* copy bits */
			encoding.bitvec.length = length;
			for (int c = 0; c < length; c++) {
				encoding.bitvec.bits[c] = bits[c];
			}
		} else {
			make_encodings_recursive(node->left, encodings, bits, 0, index + 1);
			make_encodings_recursive(node->right, encodings, bits, 1, index + 1);
		}
	}
}
