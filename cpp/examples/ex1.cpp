#include <iostream>				// std::cout
#include <string>				// std::string
#include <sstream>				// std::stringstream
#include <cstring> 				// strcmp()
#include <cstddef>				// size_t

#include "Huffman.hpp"

std::string b_vec_to_str(std::vector<bool>);

int main(int argc, char **argv)
{
	/* parse command line args, and set input if correct */
	//std::copy(argv, argv + argc, std::ostream_iterator<char *>(std::cout, "\n")); // requires <algorithm> and <iterator>
	
	std::string theString;
	if (argc == 3 && strcmp(argv[1], "-i") == 0) {
		theString = argv[2];
	}

	/* create variables */
	huffman::HuffmanTree tree = huffman::builder::build(theString);

	/* print the input */
	std::cout << "input:   [" << theString << "]" << std::endl;
	
	std::vector<bool> encoded = huffman::encoder::encode(theString,tree);
	std::cout << "encoded: [" << b_vec_to_str(encoded) << "]" << std::endl;
	
	std::string decoded = huffman::decoder::decode(encoded,tree);
	std::cout << "decoded: [" << decoded << "]" << std::endl;
}

std::string b_vec_to_str(std::vector<bool> input)
{
	std::stringstream ss;
	for (size_t c = 0; c < input.size(); c++) {
		bool current = input.at(c);
		ss << current;
	}
	return ss.str();
}
