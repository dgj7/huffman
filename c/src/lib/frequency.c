#include <stdlib.h> // exit()
#include <stdio.h> // printf()

#include "frequency.h"
#include "huffman.h"

frequency_t * count_frequencies(char *message, size_t length) {
	/* initialize the frequency array */
	size_t uniques = unique_characters(message, length);
	frequency_t *frequencies = malloc(uniques * sizeof(frequency_t));
	size_t used = 0;

	/* panic if we weren't able to get memory */
	if (frequencies == NULL) {
		printf("ERROR: %d: can't allocate memory for frequencies", ERROR_MALLOC_FREQUENCIES);
		exit(ERROR_MALLOC_FREQUENCIES);
	}

	/* count characters */
	for (int c = 0; c < length; c++) {
		char symbol = message[c];
		int index = find_matching_index(frequencies, used, symbol);
		if (index >= 0) {
			frequencies[index].frequency = frequencies[index].frequency + 1;
		} else {
			frequencies[used++] = (frequency_t) { .symbol = symbol, .frequency = 1 };
		}
	}

	/* done */
	return frequencies;
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

int find_matching_index(frequency_t *frequencies, size_t length, char symbol) {
	for (int c = 0; c < length; c++) {
		frequency_t copy = frequencies[c];
		if (copy.symbol == symbol) {
			c;
		}
	}
	return -1;
}
