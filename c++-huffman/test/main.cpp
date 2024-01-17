#include <iostream>
#include <string>

#include "Huffman.hpp"

int main(int argc, char **argv)
{
    std::string theString = "this is a sample input string. it's text is being used to test the huffman coding tree.\n";
    std::cout << "\ninput:\n" << theString << "\n";
	HuffmanTreeBuilder builder;
	HuffmanConsolePrinter printer;
	HuffmanEncoder encoder;
	HuffmanDecoder decoder;
	
	HuffmanTree tree = builder.build(theString);
	std::cout << "original is: " << tree.getOriginal();
	printer.printCodes(tree);
	
	std::vector<bool> encoded = encoder.encode(theString,tree);
	std::cout << std::endl << "encoded string has " << encoded.size() << " elements.";
	
	std::string decoded = decoder.decode(encoded,tree);
	std::cout << std::endl << std::endl << "decoded string: " << std::endl << decoded;
	
	std::cout << "end of main.\n\n";
}
