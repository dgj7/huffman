#ifndef DEBUG__DG__H__
#define DEBUG__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "huffman.h"
#include "transform.h"

const void debug_print_tree_helper(const struct node_t * const tree);
const void debug_print_encodings_helper(const struct encoding_list_t * const encodings);

const char * const printable_encoded_message(const struct encoded_message_t * const em);

#ifdef __cplusplus
}
#endif

#endif
