#include <stddef.h>		// size_t
#include <stdlib.h>		// free()
#include <stdbool.h>	// bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"
#include "encoding.h"

static void free_encoding(struct encoding_t * encoding);

struct node_t *
create_tree(
	char * message
	,int length
){
	/* gather frequency data, needed to build tree */
	struct frequency_t * frequencies = count_frequencies(message, length);

	/* build the tree */
	struct node_t * root = to_tree(frequencies);

	/* free temporary memory */
	free(frequencies->pairs);
	free(frequencies);

	/* done */
	return root;
}

struct encoding_list_t *
extract_encodings(
	struct node_t * tree
){
	return make_encodings_helper(tree, tree->tree_size);
}

void
free_tree(
	struct node_t * tree
)
{
	if (tree != NULL) {
		free_tree(tree->left);
		free_tree(tree->right);
	}
	free(tree);
}

void
free_encodings(
	struct encoding_list_t * encodings
){
	free_encoding(encodings->head);
	free(encodings);
}

static
void
free_encoding(
	struct encoding_t * encoding
){
	if (encoding->next != NULL) {
		free_encoding(encoding->next);
	}
	free(encoding->bitvec->bits);
	free(encoding->bitvec);
	free(encoding);
}
