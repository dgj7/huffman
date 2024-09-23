#include <stddef.h> // size_t
#include <stdlib.h> // free()
#include <stdbool.h> // bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"
#include "encoding.h"

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

encoding_list_t * encode(node_t * tree) {
	return make_encodings_helper(tree, tree->tree_size);
}

void free_tree(node_t * tree) {
	// todo
}

void free_encodings(encoding_list_t * encodings) {
	// todo
}
