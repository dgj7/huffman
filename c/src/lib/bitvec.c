#include <stdbool.h> // bool
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), exit()

#include "huffman.h"
#include "bitvec.h"

const int ERROR_MALLOC_BIT_ARRAY = 400;

encoding_t * make_encodings(huffman_t * tree) {
	/* handle bad input */
	if (tree == NULL) {
		return NULL;
	}

	exit(1);// todo
}

encoding_t make_encoding(node_t * node, bool * input_bits, short level, bool next) {
	/* check if we're ready to stop */
	if (node->nt == LEAF) {
		// todo
	}

	/* make storage for a bit array */
	bool * current_bits = malloc((level + 1) * sizeof(bool));
	if (current_bits == NULL) {
		printf("ERROR: %d: can't allocate memory for bit array", ERROR_MALLOC_BIT_ARRAY);
		exit(ERROR_MALLOC_BIT_ARRAY);
	}

	exit(1);// todo
}
