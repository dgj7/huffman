#ifndef __HUFFMAN__DG__H__
#define __HUFFMAN__DG__H__

#define EXPORT __attribute__((__visibility__("default")))

typedef struct {
	int value;
} huffman_t;

EXPORT huffman_t encode(char *message, int length);
EXPORT char * decode(huffman_t message);

EXPORT char * printable_encoded_message(huffman_t message);

#endif
