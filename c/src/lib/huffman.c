#include <stddef.h> // size_t
#include <stdlib.h> // free()
#include <stdbool.h> // bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"

node_t * create_tree(char * message, int length) {
	/* gather frequency data, needed to build tree */
	frequency_t * frequencies = count_frequencies(message, length);

	/* build the tree */
	node_t * root = to_tree(frequencies);

	/* free temporary memory */
	free(frequencies->pairs);
	free(frequencies);

	/* done */
	return root;
}

char * decode(node_t * encoded) {
	return "not yet implemented";
}

char * printable_encoded_message(node_t * encoded) {
	return "not yet implemented";
}
