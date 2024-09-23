#ifndef __ENCODING__DG__H__
#define __ENCODING__DG__H__

encoding_t * make_encodings_helper(node_t * tree, int length);
void make_encodings_helper_recursive(node_t * node, encoding_t * encodings, bool bits[], bool next, short index);

#endif
