#include <iostream>

#include "htree.h"

void print_code_table( std::string, std::string, HTree );
std::string get_unique_chars( std::string );
uint64_t get_frequency( std::string str, char ch );
HTree build_standard_freq_tree(  );

int main()
{
    std::string theString = "this is a sample input string. it's text is being used to test the huffman coding tree.\n";
    std::cout << "\ninput:\n" << theString << "\n";
    HTree myTree = build_huffman_tree( theString );
    std::string alphabet = get_unique_chars( theString );
    //std::string alphabet = "\n\t !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    print_code_table( alphabet, theString, myTree );

    std::cout << "\n========================================";
    std::cout << "\nencoding string, " << theString.size(  ) << "bytes/" << theString.size(  ) * 8 << "bits...";
    std::cout << "\n";
    std::vector<bool> bitStream = huffman_encode( theString, myTree );
    std::string encodedString = bits_to_string( bitStream );
    std::cout << bitStream.size(  ) / 8 << "bytes/" << bitStream.size(  ) << "bits: ";
    std::cout << encodedString;
    //for( size_t e = 0; e < bitStream.size(  ); e++ )
    //    std::cout << bitStream[e];

    std::cout << "\n========================================";
    std::cout << "\ndecoding bit stream...";
    std::string decoded = huffman_decode( bitStream, myTree );
    std::cout << "\ndecoded:\n" << decoded;

    std::cout << "\n========================================";
    std::cout << "\ndecoding encoded string...";
    std::vector<bool> bitsFromEncodedString = string_to_bits( encodedString );
    std::string decoded2 = huffman_decode( bitsFromEncodedString, myTree );
    std::cout << "\ndecoded:\n" << decoded2;

    std::cout << "\n========================================";
    std::cout << "\ncreating a tree based on standard letter freqencies";
    HTree standardTree = build_standard_freq_tree(  );
    //print_code_table( alphabet, "", standardTree );

    std::cout << "\nend of main";
    return 0;
}

void print_code_table( std::string alphabet, std::string programInputString, HTree tree )
{
    //std::cout << "\nuniques: " << alphabet << "  (" << alphabet.size(  ) << ") chars";
    std::cout << "\nLETTER\tFREQUENCY\tCODE-SIZE\tCODE";

    for( size_t c = 0; c < alphabet.size(  ); c++ )
    {
        char letter = alphabet[c];
        std::vector<bool> code = get_code( letter, tree );

        std::cout << "\n";
        if( alphabet[c] == '\n' ) std::cout << "\\n";
        else if( alphabet[c] == '\t' ) std::cout << "\\t";
        else if( alphabet[c] == ' ' ) std::cout << "[space]";
        else std::cout << alphabet[c];
        std::cout << "\t" << get_frequency( programInputString, letter )
                  << "\t\t" << code.size(  ) << "\t\t";

        if( code.size(  ) > 0 )
        {
            for( size_t d = 0; d < code.size(  ); d++ )
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

uint64_t get_frequency( std::string str, char ch )
{
    uint64_t freq = 0;

    while( str.find( ch ) != std::string::npos )
    {
        size_t loc = str.find( ch );
        str.erase( loc, 1 );
        freq++;
    }

    return freq;
}

std::string get_unique_chars( std::string input )
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

HTree build_standard_freq_tree(  )
{
    std::map<uint8_t, uint64_t> freqs;

    freqs['a'] = 11602;
    freqs['b'] = 4702;
    freqs['c'] = 3511;
    freqs['d'] = 2670;
    freqs['e'] = 2007;
    freqs['f'] = 3779;
    freqs['g'] = 1950;
    freqs['h'] = 7232;
    freqs['i'] = 6286;
    freqs['j'] = 597;
    freqs['k'] = 590;
    freqs['l'] = 2705;
    freqs['m'] = 4374;
    freqs['n'] = 2365;
    freqs['o'] = 6264;
    freqs['p'] = 2545;
    freqs['q'] = 173;
    freqs['r'] = 1653;
    freqs['s'] = 7755;
    freqs['t'] = 16671;
    freqs['u'] = 1487;
    freqs['v'] = 649;
    freqs['w'] = 6753;
    freqs['x'] = 37;
    freqs['y'] = 1620;
    freqs['z'] = 34;

    HTree tree = build_huffman_tree( freqs );

    return tree;
}



