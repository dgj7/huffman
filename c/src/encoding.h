#ifndef ENCODING__DG__H__
#define ENCODING__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


const struct encoding_list_t * const make_encodings_helper(const struct node_t * const tree, const int length);

const int count_encodings(const struct encoding_list_t * list);


#ifdef __cplusplus
}
#endif

#endif
