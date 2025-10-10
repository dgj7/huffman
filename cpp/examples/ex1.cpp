#include <iostream>				// std::cout
#include <string>				// std::string
#include <cstring> 				// strcmp()
#include <numeric>              // std::accumulate

#include "huffman.hpp"

/**
 * Read a string from terminal and print it's encoded bit interpretation.
 */
int main(int argc, char **argv)
{
	/* print out command-line args */
	//std::copy(argv, argv + argc, std::ostream_iterator<char *>(std::cout, "\n")); // requires <algorithm> and <iterator>

	/* grab arg */
	std::string theString;
	if (argc == 3 && strcmp(argv[1], "-i") == 0) {
		theString = argv[2];
	}

	/* create variables */
	const huffman::Tree * tree = huffman::builder::build(theString);

	/* print the input */
	std::cout << "input:   [" << theString << "]" << std::endl;
	std::vector<bool> encoded = huffman::encoder::encode(theString, *tree);
	std::string encoded_string = std::accumulate(encoded.begin(), encoded.end(), std::string(), [](const std::string & accumulator, bool value){return accumulator + (value ? "1" : "0");});
	std::cout << "encoded: [" << encoded_string << "]" << std::endl;
	std::string decoded = huffman::decoder::decode(encoded, *tree);
	std::cout << "decoded: [" << decoded << "]" << std::endl;
}
