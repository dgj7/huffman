#ifndef __ENCODING__DG__H__
#define __ENCODING__DG__H__
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 * INTERNAL API
 *****************************************************************************/
encoding_list_t * make_encodings_helper(node_t * tree, int length);

/******************************************************************************
 * SUPPORT FUNCTIONS
 *****************************************************************************/
void make_encodings_helper_recursive(node_t * node, encoding_list_t * list, bool bits[], bool next, short index);
void populate_encoding(encoding_t * encoding, node_t * node, bool bits[], int length);
void debug_print_encodings(encoding_t * encodings);


#ifdef __cplusplus
}
#endif
#endif
