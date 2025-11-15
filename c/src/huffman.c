#include <stddef.h>		// size_t
#include <stdlib.h>		// free()
#include <stdbool.h>	// bool

#include "huffman.h"
#include "frequency.h"
#include "tree.h"
#include "encoding.h"
#include "debug.h"

static const void free_encoding(const struct encoding_t * const encoding);

const struct node_t * const
create_tree(
	const char * const message
	,const int length
){
	/* gather frequency data, needed to build tree */
	const struct frequency_t * const frequencies = count_frequencies(message, length);

	/* build the tree */
	const struct node_t * const root = to_tree(frequencies);

	/* free temporary memory */
	if (frequencies != NULL)
	{
		free(frequencies->pairs);
		free((void*)frequencies);
	}

	/* done */
	return root;
}

const struct encoding_list_t * const
extract_encodings(
	const struct node_t * const tree
){
	return make_encodings_helper(tree, tree_size(tree));
}

const void
free_tree(
	const struct node_t * const tree
)
{
	if (tree != NULL) {
		free_tree(tree->left);
		free_tree(tree->right);
	}
	free((void*)tree);
}

const void
free_encodings(
	const struct encoding_list_t * const encodings
){
	free_encoding(encodings->head);
	free((void*)encodings);
}

static
const void
free_encoding(
	const struct encoding_t * const encoding
){
	if (encoding->next != NULL) {
		free_encoding(encoding->next);
	}
	free(encoding->bitvec->bits);
	free(encoding->bitvec);
	free((void*)encoding);
}

const void
debug_print_tree(
	const struct node_t * const tree
){
	debug_print_tree_helper(tree);
}

const void
debug_print_encodings(
	const struct encoding_list_t * const encodings
){
	debug_print_encodings_helper(encodings);
}
