#ifndef __ENCODING__DG__H__
#define __ENCODING__DG__H__

encoding_t * make_encodings(node_t * tree);
void make_encodings_recursive(node_t * node, encoding_t * encodings, bool bits[], bool next, short index);

#endif
