#ifndef __HUFFMAN__DG__H__
#define __HUFFMAN__DG__H__

#define EXPORT __attribute__((__visibility__("default")))

typedef enum { INTERNAL = 98, LEAF = 99 } nodetype_t;

typedef struct _node_t node_t;
typedef struct _node_t {
	long frequency;
	char symbol;
	nodetype_t nt;
	node_t *left;
	node_t *right;
	short tree_size;
} node_t;

EXPORT node_t * create_tree(char * message, int length);

EXPORT char * decode(node_t * message);
EXPORT char * printable_encoded_message(node_t * message);

#endif
