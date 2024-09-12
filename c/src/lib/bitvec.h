#ifndef __BITVEC__DG__H__
#define __BITVEC__DG__H__

typedef struct {
	short length;
	bool * bits;
} bitvec_t;

typedef struct {
	bitvec_t bitvec;
	char symbol;
} encoding_t;

encoding_t * make_encodings(huffman_t * tree);
void make_encodings_recursive(node_t * node, encoding_t * encodings, bool bits[], bool next, short index);

#endif
