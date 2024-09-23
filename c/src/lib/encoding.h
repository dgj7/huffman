#ifndef __ENCODING__DG__H__
#define __ENCODING__DG__H__

encoding_list_t * make_encodings_helper(node_t * tree, int length);
void make_encodings_helper_recursive(node_t * node, encoding_list_t * list, bool bits[], bool next, short index);

int count_length(encoding_t * encodings);
void populate_encoding(encoding_t * encoding, node_t * node, bool bits[], int length);

void debug_print_encodings(encoding_t * encodings);

#endif
