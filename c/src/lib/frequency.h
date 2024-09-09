#ifndef __FREQUENCY__DG__H__
#define __FREQUENCY__DG__H__

const int ERROR_MALLOC_FREQUENCIES = 200;

typedef struct {
	long frequency;
	char symbol;
} frequency_t;

frequency_t * count_frequencies(char *message, size_t length);
size_t unique_characters(char *message, size_t length);
int find_matching_index(frequency_t * frequencies, size_t length, char symbol);

#endif
