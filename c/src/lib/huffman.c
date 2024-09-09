#include <stddef.h> // size_t

#include "huffman.h"
#include "frequency.h"

huffman_t encode(char *message, int length) {
	frequency_t frequency = count_frequencies(message, length);
	return (huffman_t) {.value = 1};
}

char * decode(huffman_t encoded) {
	return "not yet implemented";
}

char * printable_encoded_message(huffman_t encoded) {
	return "not yet implemented";
}
