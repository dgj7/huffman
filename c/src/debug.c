#include <stdio.h>
#include <stdlib.h> 		// malloc(), free()

#include "debug.h"
#include "frequency.h"
#include "tree.h"
#include "transform.h"

static const int ERROR_MALLOC_PRINTABLE_MESSAGE = 500;

static int node_index = 0;

static const void debug_print_tree_recursive(const struct node_t * const node);

static const int round_up_next_power_two(unsigned int n);
static const void debug_print_line_end_or_comma(int next);

const void
debug_print_tree_helper(
    const struct node_t * const tree
){
    /* reset everything */
    node_index = 0;

    /* print the things */
    printf("==========\n");
    printf("tree, size %d, has %d leaves\n", tree_size(tree), leaf_count(tree));
    printf("----------\n");
    debug_print_tree_recursive(tree);
    printf("\n");
    printf("----------\n");
    printf("==========\n");

    /* reset everything */
    node_index = 0;
}

const void
debug_print_encodings_helper(
    const struct encoding_list_t * const encodings
){
    printf("==========\n");
    if (encodings == NULL)
    {
        printf("==========\n");
        return;
    }

    struct encoding_t * node = encodings->head;
    while (node != NULL)
    {
        printf("%c: ", node->symbol);
        if (node->bitvec != NULL)
        {
            for (int c = 0; c < node->bitvec->length; c++)
            {
                printf("%c", node->bitvec->bits[c] ? '1' : '0');
            }
        }
        printf("\n");
        node = node->next;
    }
    printf("==========\n");
}

const char * const
printable_encoded_message(
	const struct encoded_message_t * const em
){
	/* allocate memory for output string */
	char * const output = malloc((em->length + 1) * sizeof(char));
	if (output == NULL) {
		printf("ERROR: %d: can't allocate memory for printable encoded message", ERROR_MALLOC_PRINTABLE_MESSAGE);
		exit(ERROR_MALLOC_PRINTABLE_MESSAGE);
	}

	/* copy bits */
	for (int idx = 0; idx < em->length; idx++) {
		output[idx] = em->bits[idx] ? '1' : '0';
	}

    /* null terminate */
    output[em->length] = '\0';

	/* done */
	return output;
}

static
const void
debug_print_tree_recursive(
    const struct node_t * const node
){
    node_index += 1;
    int next = round_up_next_power_two(node_index);

    if (node->nt == INTERNAL)
    {
        printf("(%lu)", node->frequency);
        debug_print_line_end_or_comma(next);

        debug_print_tree_recursive(node->left);
        debug_print_tree_recursive(node->right);
    }
    else
    {
        printf("[%c(%lu)]", node->symbol, node->frequency);
        debug_print_line_end_or_comma(next);
    }
}

static
const int
round_up_next_power_two(
    unsigned int n
){
    if (n == 0) {
        return 1; // Or handle as an error, depending on requirements
    }
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

static
const void
debug_print_line_end_or_comma(
    int next
){
    if (node_index == 1 || node_index == next-1)
    {
        printf("\n");
    }
    else
    {
        printf(", ");
    }
}
