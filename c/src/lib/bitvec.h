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

typedef struct {
	short length;
	encoding_t * encodings;
} encoding_info_t;

encoding_t * make_encodings(node_t * tree);
void make_encodings_recursive(node_t * node, encoding_t * encodings, bool bits[], bool next, short index);

#endif
