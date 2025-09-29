#ifndef FREQUENCY__DG__H__
#define FREQUENCY__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


struct frequency_pair_t {
	long frequency;
	char symbol;
};

struct frequency_t {
	long count;
	struct frequency_pair_t *pairs;
};

struct frequency_t * count_frequencies(char *message, size_t length);


#ifdef __cplusplus
}
#endif

#endif
