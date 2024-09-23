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

char * printable_encoded_message(char * message, encoding_t * encodings);
char * decode(char * encoded, encoding_t * encodings);

int main(int argc, char **argv) {
	clock_t start = clock();

	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			size_t length = strlen(argv[IDX_MESSAGE]);
			char *message = malloc(length);
			if (message) {
				strcpy(message, argv[IDX_MESSAGE]);

				node_t * tree = create_tree(message, length);
				encoding_t * encodings = encode(tree);

				char *encoded = printable_encoded_message(message, encodings);
				char *decoded = decode(encoded, encodings);

				printf("input:   [%s]\n", message);
				printf("encoded: [%s]\n", encoded);
				printf("decoded: [%s]\n", decoded);

				free_tree(tree);
				free_encodings(encodings);
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

	/* declare success, print profiling info */
	clock_t elapsed = clock() - start;
	double ms = (((double)elapsed)/CLOCKS_PER_SEC)/1000;
	printf("done. (%.0lf ms)\n", ms);

	/* done */
	return 0;
}

char * printable_encoded_message(char * message, encoding_t * encodings) {
	return "not yet implemented";
}

char * decode(char * encoded, encoding_t * encodings) {
	return "not yet implemented";
}
