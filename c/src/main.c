#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/huffman.h"

const int IDX_ARG = 1;
const int IDX_MESSAGE = 2;
const int ERROR_READ = 1;
const int ERROR_UNKNOWN_ARG = 2;
const int ERROR_UNKNOWN_ARG_COUNT = 3;

int main(int argc, char **argv) {
	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			int length = strlen(argv[IDX_MESSAGE]);
			char *message = malloc(length);
			if (message) {
				strcpy(message, argv[IDX_MESSAGE]);
				int result = encode(message, length);
				printf("huffman result: %d\n", result);
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
