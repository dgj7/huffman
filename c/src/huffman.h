#ifndef HUFFMAN__DG__H__
#define HUFFMAN__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // bool


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

node_t * create_tree(char * message, int length);
encoding_list_t * extract_encodings(node_t * tree);
void free_tree(node_t * tree);
void free_encodings(encoding_list_t * list);


#ifdef __cplusplus
}
#endif

#endif
