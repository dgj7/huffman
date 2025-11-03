#include <stdio.h> 			// printf()
#include <string.h> 		// strcpy(), strlen(), strncat()
#include <stdlib.h> 		// malloc(), free()
#include <stdlib.h> 		// exit()

#include "huffman.h"		// huffman library
#include "transform.h"		// encode(), decode()
#include "debug.h"			// printable_encoded_message()

static const int IDX_ARG = 1;
static const int IDX_MESSAGE = 2;

static const int ERROR_READ = 1;
static const int ERROR_UNKNOWN_ARG = 2;
static const int ERROR_UNKNOWN_ARG_COUNT = 3;

const int
main(
	const int argc
	,const char ** const argv
){
	if (argc == 3) {
		if (strcmp(argv[IDX_ARG], "-i") == 0) {
			const size_t length = strlen(argv[IDX_MESSAGE]);
			const char * const message = malloc(length);
			if (message) {
				/* copy the message into somewhere it's usable */
				strcpy((char*)message, argv[IDX_MESSAGE]);

				/* create huffman-related data structures */
				const struct node_t * const tree = create_tree(message, length);
				const struct encoding_list_t * const encodings = extract_encodings(tree);

				/* do transformations with the huffman data */
				const struct encoded_message_t * const encoded = encode(message, encodings);
				const char * const printable = printable_encoded_message(encoded);
				const char * const decoded = decode(encoded, tree, length);

				/* do debug things */
				//debug_print_tree(tree);
				//debug_print_encodings(encodings);

				/* print results */
				printf("input:   [%s]\n", message);
				printf("encoded: [%s]\n", printable);
				printf("decoded: [%s]\n", decoded);

				/* free memory */
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

	/* done */
	return 0;
}
