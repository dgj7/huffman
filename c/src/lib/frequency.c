#include <stdlib.h> // exit()
#include <stdio.h> // printf()

#include "frequency.h"
#include "huffman.h"

const int ERROR_MALLOC_FREQUENCIES = 200;

frequency_t count_frequencies(char *message, size_t length) {
	/* initialize the frequency array */
	frequency_t wrapper;
	size_t uniques = unique_characters(message, length);
	wrapper.pairs = malloc(uniques * sizeof(frequency_pair_t));
	int used = 0;

	/* panic if we weren't able to get memory */
	if (wrapper.pairs == NULL) {
		printf("ERROR: %d: can't allocate memory for frequencies", ERROR_MALLOC_FREQUENCIES);
		exit(ERROR_MALLOC_FREQUENCIES);
	}

	/* count characters */
	for (int c = 0; c < length; c++) {
		char symbol = message[c];
		int index = find_matching_index(wrapper.pairs, used, symbol);
		if (index >= 0) {
			wrapper.pairs[index].frequency = wrapper.pairs[index].frequency + 1;
		} else {
			wrapper.pairs[used] = (frequency_pair_t) { .symbol = symbol, .frequency = 1 };
			used++;
		}
	}

	/* update structure */
	wrapper.count = used;

	/* debug only */
	//printf("frequency_t.count=[%d]\n", wrapper.count);
	//for (int d = 0; d < used; d++) {
	//	printf("\tfrequency_t[%d]: .symbol=[%c], .frequency=[%d]\n", d, wrapper.pairs[d].symbol, wrapper.pairs[d].frequency);
	//}

	/* done */
	return wrapper;
}

size_t unique_characters(char *message, size_t length) {
	if (message) {
		size_t count = 0;
		for (size_t i = 0; i < length; i++) {
			short flag = 0;
			for (size_t j = 0; j < i; j++) {
				char left = message[i];
				char right = message[j];
				if (left == right) {
					flag = 1;
					break;
				}
			}

			if (flag == 0) {
				count++;
			}
		}
		return count;
	}
	return 0;
}

int find_matching_index(frequency_pair_t *frequencies, size_t length, char symbol) {
	for (int c = 0; c < length; c++) {
		char potential = frequencies[c].symbol;
		if (potential == symbol) {
			return c;
		}
	}
	return -1;
}
