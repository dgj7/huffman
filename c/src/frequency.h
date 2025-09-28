#ifndef FREQUENCY__DG__H__
#define FREQUENCY__DG__H__

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	long frequency;
	char symbol;
} frequency_pair_t;

typedef struct {
	long count;
	frequency_pair_t *pairs;
} frequency_t;

frequency_t * count_frequencies(char *message, size_t length);


#ifdef __cplusplus
}
#endif

#endif
