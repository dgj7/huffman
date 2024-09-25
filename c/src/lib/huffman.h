#ifndef __HUFFMAN__DG__H__
#define __HUFFMAN__DG__H__
#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h> // bool

#define EXPORT __attribute__((__visibility__("default")))

typedef enum { INTERNAL = 98, LEAF = 99 } nodetype_t;
typedef enum { LEFT = false, RIGHT = true } tree_dir_t;

typedef struct _node_t node_t;
typedef struct _node_t {
	long frequency;
	char symbol;
	nodetype_t nt;
	node_t *left;
	node_t *right;
	short tree_size;
} node_t;

typedef struct {
	short length;
	bool * bits;
} bitvec_t;

typedef struct _encoding_t encoding_t;
typedef struct _encoding_t {
	bitvec_t * bitvec;
	char symbol;
	encoding_t * next;
} encoding_t;

typedef struct {
	encoding_t * head;
} encoding_list_t;

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
