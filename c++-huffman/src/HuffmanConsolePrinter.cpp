#include "Huffman.hpp"

#include <iostream>

void HuffmanConsolePrinter::printCodes(HuffmanTree tree)
{
	std::string alphabet = getUniqueSymbols(tree.getOriginal());
    std::cout << "\nLETTER\tFREQUENCY\tCODE-SIZE\tCODE";

    for(size_t c = 0; c < alphabet.size(); c++)
    {
        char letter = alphabet[c];
        std::vector<bool> code = encoder.getCode(letter, tree);

        std::cout << "\n";
        if( alphabet[c] == '\n' ) std::cout << "\\n";
        else if( alphabet[c] == '\t' ) std::cout << "\\t";
        else if( alphabet[c] == ' ' ) std::cout << "[space]";
        else std::cout << alphabet[c];
        std::cout << "\t" << encoder.getFrequency(tree.getOriginal(), letter)
                  << "\t\t" << code.size() << "\t\t";

        if(code.size() > 0)
        {
            for(size_t d = 0; d < code.size(); d++)
            {
                std::cout << code[d];
            }
        }
        else
        {
            std::cout << "no such code exists.";

        }
    }
}

std::string HuffmanConsolePrinter::getUniqueSymbols(std::string input)
{
	std::string uniques = "";

    for( size_t c = 0; c < input.size(  ); c++ )
    {
        char current = input[c];

        if( uniques.find( current ) == std::string::npos )
            uniques += current;
    }

    return uniques;
}
