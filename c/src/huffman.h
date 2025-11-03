#ifndef HUFFMAN__DG__H__
#define HUFFMAN__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h> // bool


enum nodetype_t { INTERNAL = 98, LEAF = 99 };
enum tree_dir_t { LEFT = false, RIGHT = true };

struct node_t {
	long frequency;
	char symbol;
	enum nodetype_t nt;
	struct node_t *left;
	struct node_t *right;
	// todo: remove this? tree_size seems strange here
	short tree_size;
};

struct bitvec_t {
	short length;
	bool * bits;
};

struct encoding_t {
	struct bitvec_t * bitvec;
	char symbol;
	struct encoding_t * next;
};

struct encoding_list_t {
	struct encoding_t * head;
};

const struct node_t * const create_tree(const char * const message, const int length);
const struct encoding_list_t * const extract_encodings(const struct node_t * const tree);

const void free_tree(const struct node_t * const tree);
const void free_encodings(const struct encoding_list_t * const list);

const void debug_print_tree(const struct node_t * const tree);
const void debug_print_encodings(const struct encoding_list_t * const encodings);


#ifdef __cplusplus
}
#endif

#endif
