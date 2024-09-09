#ifndef __HUFFMAN__DG__H__
#define __HUFFMAN__DG__H__

#define EXPORT __attribute__((__visibility__("default")))

typedef enum { INTERNAL = 0, LEAF = 1 } nodetype_t;

struct node_t;
typedef struct {
	long frequency;
	char symbol;
	nodetype_t nt;
	struct node_t *left;
	struct node_t *right;
} node_t;

typedef struct {
	int value;
} huffman_t;

EXPORT huffman_t encode(char *message, int length);
EXPORT char * decode(huffman_t message);

EXPORT char * printable_encoded_message(huffman_t message);

#endif
