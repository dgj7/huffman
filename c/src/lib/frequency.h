#ifndef __FREQUENCY__DG__H__
#define __FREQUENCY__DG__H__

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

frequency_t * count_frequencies(char *message, size_t length);// todo: this method should return a pointer (dynamically allocated)
size_t unique_characters(char *message, size_t length);
int find_matching_index(frequency_pair_t * frequencies, size_t length, char symbol);

#ifdef __cplusplus
}
#endif

#endif
