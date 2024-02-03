#include <iostream>
#include <string>
#include <sstream>
#include <cstring> // strcmp()

#include "lib/Huffman.hpp"

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
	HuffmanTreeBuilder builder;
	HuffmanConsolePrinter printer;
	HuffmanEncoder encoder;
	HuffmanDecoder decoder;
	HuffmanTree tree = builder.build(theString);

	/* print the input */
	std::cout << "input:  " << theString << std::endl;

	// todo: this might need to be moved to a -verbose mode, or something similar
	//printer.printCodes(tree);
	
	std::vector<bool> encoded = encoder.encode(theString,tree);
	std::cout << "encoded: " << b_vec_to_str(encoded) << std::endl;
	
	std::string decoded = decoder.decode(encoded,tree);
	std::cout << "decoded: " << decoded << std::endl;
}

std::string b_vec_to_str(std::vector<bool> input)
{
	std::stringstream ss;
	for (int c = 0; c < input.size(); c++) {
		bool current = input.at(c);
		ss << current;
	}
	return ss.str();
}
