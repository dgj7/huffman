#ifndef __BITVEC__DG__H__
#define __BITVEC__DG__H__

typedef struct {
	short length;
	bool * bits;
} bitvec_t;

typedef struct {
	short length;
	bitvec_t encoding;
	char symbol;
} encoding_t;

encoding_t * make_encodings(huffman_t * tree);

encoding_t make_encoding(node_t * node, bool * input_bits, short level, bool next);

#endif
