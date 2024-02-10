#include "Huffman.hpp"

#include <bitset>

std::vector<bool> HuffmanEncoder::encode(std::string input, HuffmanTree tree)
{
	std::vector<bool> bits;

    for(size_t c = 0; c < input.size(); c++)
    {
        char current = input[c];
        std::vector<bool> letterCode = getCode(current, tree);
        if(letterCode.size() > 0)
        {
            for(size_t d =0; d < letterCode.size(); d++)
            {
                bits.push_back(letterCode[d]);
            }
        }
    }

    return bits;
}

std::vector<bool> HuffmanEncoder::getCode(uint8_t code, HuffmanTree tree)
{
	bool path[65535];	// max size of wide char
	std::vector<bool> retval;

	retval.clear();
	getCodeHelper(code, tree._root, tree._root, 0, path, 0, retval);

	return retval;
}

void HuffmanEncoder::getCodeHelper(uint8_t code, HuffmanNode *node, HuffmanNode *root, bool preDirection, bool path[], uint64_t pathLen, std::vector<bool> &ret)
{
	if(node == NULL)
		return;

	if(node == root)
	{
		// don't do anything, didnt come from left or right
	}
	else
	{
		if(preDirection == 0)
			path[pathLen] = 0;
		else
			path[pathLen] = 1;

		pathLen++;
	}

	// if it's a leaf node AND it's the one we're looking for, return the data
	if(node->_left == NULL && node->_right == NULL)
	{
		if(node->_data == code)
		{
			for(uint64_t c = 0; c < pathLen; c++)
			{
				ret.push_back( path[c] );
			}
		}
	}
	else
	{
		getCodeHelper(code, node->_left, root, 0, path, pathLen, ret);
		getCodeHelper(code, node->_right, root, 1, path, pathLen, ret);
	}
}

std::vector<bool> HuffmanEncoder::stringToBits(std::string text)
{
    std::vector<bool> bits;

    for(size_t c = 0; c < text.size(); c++)
    {
        char ch = text[c];
        std::bitset<8> byte( (short)ch );

        for(size_t bit = 0; bit < byte.size(); bit++)
        {
            bits.push_back(byte[bit]);
        }
    }

    return bits;
}

uint64_t HuffmanEncoder::getFrequency(std::string str, char ch)
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
