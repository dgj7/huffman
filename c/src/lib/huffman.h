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

typedef struct {
	node_t *root;
} huffman_t;

EXPORT huffman_t * encode(char *message, int length);
EXPORT char * decode(huffman_t * message);

EXPORT char * printable_encoded_message(huffman_t * message);

#endif
