#ifndef TYPES__DG__H__
#define TYPES__DG__H__

#include <stdbool.h>

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

// todo: this structure requires 8 times as much storage as needed; rewrite using int array
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

#endif
