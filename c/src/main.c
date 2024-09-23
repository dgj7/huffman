#include <stdio.h> // printf()
#include <string.h> // strcpy(), strlen(), strncat()
#include <stdlib.h> // malloc(), free()
#include <time.h> // clock_t, CLOCKS_PER_SEC
#include <stdlib.h> // exit()

#include "lib/huffman.h"

const int IDX_ARG = 1;
const int IDX_MESSAGE = 2;

const int ERROR_READ = 1;
const int ERROR_UNKNOWN_ARG = 2;
const int ERROR_UNKNOWN_ARG_COUNT = 3;
const int ERROR_NO_SYMBOL_MATCH = 4;
const int ERROR_MALLOC_PRINTABLE_ENCODED_MESSAGE = 5;

char * printable_encoded_message(char * message, encoding_list_t * encodings);
char * decode(char * encoded, encoding_list_t * encodings);

encoding_t * find_encoding_by_symbol(encoding_list_t * list, char symbol_key);

int main(int argc, char **argv) {
	clock_t start = clock();

	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			size_t length = strlen(argv[IDX_MESSAGE]);
			char *message = malloc(length);
			if (message) {
				strcpy(message, argv[IDX_MESSAGE]);

				node_t * tree = create_tree(message, length);
				encoding_list_t * encodings = encode(tree);

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

char * printable_encoded_message(char * message, encoding_list_t * list) {
	/* determine the length of the outgoing encoded string; start at 1 to include \0 */
	int out_len = 1;
	for (int msg_idx = 0; msg_idx < strlen(message); msg_idx++) {
		char symbol_key = message[msg_idx];
		encoding_t * encoding = find_encoding_by_symbol(list, symbol_key);
		out_len = out_len + encoding->bitvec->length;
	}

	/* allocate memory for the output string */
	char * output = malloc(out_len * sizeof(char));
	if (output == NULL) {
		printf("ERROR: %d: can't allocate memory for printable encoded message string\n", ERROR_MALLOC_PRINTABLE_ENCODED_MESSAGE);
		exit(ERROR_MALLOC_PRINTABLE_ENCODED_MESSAGE);
	}

	/* find and append the matching bits to the output string */
	int out_idx = 0;
	for (int msg_idx = 0; msg_idx < strlen(message); msg_idx++) {
		char symbol_key = message[msg_idx];
		encoding_t * encoding = find_encoding_by_symbol(list, symbol_key);
		for (int bit_idx = 0; bit_idx < encoding->bitvec->length; bit_idx++) {
			output[out_idx] = encoding->bitvec->bits[bit_idx] ? '1' : '0';
			out_idx++;
		}
	}

	/* todo */
	return output;
}

char * decode(char * encoded, encoding_list_t * list) {
	return "not yet implemented";
}

encoding_t * find_encoding_by_symbol(encoding_list_t * list, char symbol_key) {
	/* loop over to find match */
	encoding_t * encoding = list->head;
	while (encoding->next != NULL) {
		if (encoding->symbol == symbol_key) {
			break;
		}
		encoding = encoding->next;
	}

	/* error if no match is found */
	if (encoding->symbol != symbol_key) {
		printf("ERROR: %d: can't find match for symbol [%c]\n", ERROR_NO_SYMBOL_MATCH, symbol_key);
		exit(ERROR_NO_SYMBOL_MATCH);
	}

	/* done */
	return encoding;
}
