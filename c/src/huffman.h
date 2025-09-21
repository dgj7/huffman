#ifndef __HUFFMAN__DG__H__
#define __HUFFMAN__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // bool
#include "types.h"

#define EXPORT __attribute__((__visibility__("default")))

/******************************************************************************
 * PUBLIC LIBRARY API
 *****************************************************************************/
EXPORT node_t * create_tree(char * message, int length);
EXPORT encoding_list_t * create_encodings(node_t * tree);
EXPORT void free_tree(node_t * tree);
EXPORT void free_encodings(encoding_list_t * list);

/******************************************************************************
 * SUPPORT FUNCTIONS
 *****************************************************************************/
void free_encoding(encoding_t * encoding);


#ifdef __cplusplus
}
#endif

#endif
