#ifndef TRANSFORM__DG__H__
#define TRANSFORM__DG__H__

#ifdef __cplusplus
extern "C" {
#endif

struct encoded_message_t {
	bool * bits;
	int length;
};

const struct encoded_message_t * const encode(const char * const message, const struct encoding_list_t * const list);
const char * const decode(const struct encoded_message_t * const encoded, const struct node_t * const tree, const int msg_len);

#ifdef __cplusplus
}
#endif

#endif
