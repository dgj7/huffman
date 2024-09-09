#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "htree.h"
//#include "common.h"

void print_line( stringtype );
stringtype shuffle( stringtype );

int main( int argc, char **argv )
{
	//stringtype inputstring = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuddddddddddddddddddddddddddddddddddddddddddllllllllllllllllllllllllllllllllllllllllllccccccccccccccccccccccccccccccccmmmmmmmmmmmmmmmmmmmmmmmmzzkkkkkkk";
	
	stringtype inputstring = "this is a sample input string. it's text is being used to test the huffman coding tree.\n";
	std::cout << "Text to be compressed:\n";
	std::cout << inputstring << "\n";
	inputstring = shuffle( inputstring );
	
	HuffmanTree myht( inputstring, compressString );
	
	std::cout << "\n\n\ngetting codes by calling HuffmanTree::get_code_for_symbol()\n";
	Data symbol = 'c';
	std::cout << "searching for " << symbol << "...\n";
	std::vector<bool> code;
	if( myht.get_code_for_symbol( symbol, code ) )
	{
		std::cout << "code for symbol \'" << symbol << "\':\t";
		for( size_t i = 0; i < code.size(  ); i++ )
			std::cout << code[i];
	}
	else
	{
		std::cout << "could not find code for symbol \'" << symbol << "\'\n";
	}
	
	
	//std::cout << "\n\n***************************************\n"
	//	  << "testing code to read in/compress a file\n";
	
	//HuffmanTree myht2( "file.dat", compressFile );
	
	
	
	std::cout << "\n\n*****TEST COMPLETE*****";
	return 0;
}

void print_line( stringtype message )
{
	std::cout << std::endl;
	for( int i = 0; i < 20; i++ )
		std::cout << "~";
	std::cout << "\n" << message << "\n";
	for( int i = 0; i < 20; i++ )
		std::cout << "~";
}

stringtype shuffle( stringtype input )
{
	size_t insize = input.size(  );
	srand( ( unsigned ) time( 0 ) );
	
	for( int h = 0; h < insize; h++ )
	{
		for( int i = 0; i < insize; i++ )
		{
			char temp = input[i];
			int swapindex = rand(  ) % ( insize - 1 );
			input[i] = input[swapindex];
			input[swapindex] = temp;
		}
	}
	
	return input;
}
