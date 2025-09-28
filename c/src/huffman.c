#include <stddef.h> // size_t
#include <stdlib.h> // free()
#include <stdbool.h> // bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"
#include "encoding.h"

static void free_encoding(encoding_t * encoding);

node_t * create_tree(char * message, int length)
{
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

encoding_list_t * create_encodings(node_t * tree)
{
	return make_encodings_helper(tree, tree->tree_size);
}

void free_tree(node_t * tree)
{
	if (tree != NULL) {
		free_tree(tree->left);
		free_tree(tree->right);
	}
	free(tree);
}

void free_encodings(encoding_list_t * encodings)
{
	free_encoding(encodings->head);
	free(encodings);
}

static void free_encoding(encoding_t * encoding)
{
	if (encoding->next != NULL) {
		free_encoding(encoding->next);
	}
	free(encoding->bitvec->bits);
	free(encoding->bitvec);
	free(encoding);
}
