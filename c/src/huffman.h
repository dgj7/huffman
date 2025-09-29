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

struct node_t * create_tree(char * message, int length);
struct encoding_list_t * extract_encodings(struct node_t * tree);
void free_tree(struct node_t * tree);
void free_encodings(struct encoding_list_t * list);


#ifdef __cplusplus
}
#endif

#endif
