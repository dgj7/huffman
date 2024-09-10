#include <stdio.h> // printf()
#include <string.h> // strcpy(), strlen()
#include <stdlib.h> // malloc(), free()
#include <time.h> // clock_t, CLOCKS_PER_SEC

#include "lib/huffman.h"

const int IDX_ARG = 1;
const int IDX_MESSAGE = 2;
const int ERROR_READ = 1;
const int ERROR_UNKNOWN_ARG = 2;
const int ERROR_UNKNOWN_ARG_COUNT = 3;

double compute_elapsed(clock_t start);

int main(int argc, char **argv) {
	clock_t start = clock();

	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			size_t length = strlen(argv[IDX_MESSAGE]);
			char *message = malloc(length);
			if (message) {
				strcpy(message, argv[IDX_MESSAGE]);
				huffman_t * tree = encode(message, length);
				char *encoded = printable_encoded_message(tree);
				char *decoded = decode(tree);

				printf("input:   [%s]\n", message);
				printf("encoded: [%s]\n", encoded);
				printf("decoded: [%s]\n", decoded);

				free(tree);

				printf("done. (%.0lf ms)\n", compute_elapsed(start));
			} else {
				printf("ERROR: can't read message: %s", argv[IDX_MESSAGE]);
				return ERROR_READ;
			}
		} else {
			printf("ERROR: unknown arg: %s\n", argv[IDX_ARG]);
			return ERROR_UNKNOWN_ARG;
		}
	} else {
		printf("Error: unknown arg count: %d\n", argc);
		return ERROR_UNKNOWN_ARG_COUNT;
	}

	return 0;
}

double compute_elapsed(clock_t start) {
	clock_t elapsed = clock() - start;
	return (((double)elapsed)/CLOCKS_PER_SEC)/1000;
}
