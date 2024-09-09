#include <stdio.h>

#include "lib/huffman.h"

int main(int argc, char **argv) {
	char message[] = "this is a message\0";
	int result = encode(message);
	printf("temporary huffman result: %d\n", result);

	return 0;
}
