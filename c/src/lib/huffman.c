#include <stddef.h> // size_t
#include <stdlib.h> // free()

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

huffman_t * encode(char *message, int length) {
	/* gather frequency data, needed to build tree */
	frequency_t * frequency = count_frequencies(message, length);

	/* build the tree */
	huffman_t * tree = to_tree(frequency);

	/* free temporary memory */
	free(frequency->pairs);
	free(frequency);

	/* done */
	return tree;
}

char * decode(huffman_t * encoded) {
	return "not yet implemented";
}

char * printable_encoded_message(huffman_t * encoded) {
	return "not yet implemented";
}
