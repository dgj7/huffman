#include "Huffman.hpp"

#include <bitset>

std::string HuffmanDecoder::decode(std::vector<bool> bitStream, HuffmanTree tree)
{
	std::string ret = "";

    std::vector<bool> bitStreamWithoutPadding;
    for(size_t x = 3; x < bitStream.size(); x++)
        bitStreamWithoutPadding.push_back(bitStream[x]);

    // algorithm:
    // one bit at a time, pass as a code to get_symbol
    // if the current bit stream isnt a code, add the next
    // bit and try again.
    // when it is a code, remove those from the main bitstream and start over
    // also add the found code to the return string
    while(bitStreamWithoutPadding.size() > 0)
    {
        bool haveCode = false;
        size_t ct = 0;
        uint8_t letter;
        while( !haveCode )
        {
            std::vector<bool> bits;
            for(size_t c = 0; c < ct; c++)
            {
                bits.push_back(bitStreamWithoutPadding[c]);
            }

            haveCode = getSymbol(bits, letter, tree);

            ct++;
        }

        ret += char(letter);

        // now erase the first ct elements from bitStream
        ct--;
        bitStreamWithoutPadding.erase(bitStreamWithoutPadding.begin(), bitStreamWithoutPadding.begin() + ct);
    }

    return ret;
}

bool HuffmanDecoder::getSymbol(std::vector<bool> bitStream, uint8_t &symbol, HuffmanTree tree)
{
    HuffmanNode *currentNode = tree._root;

    if(bitStream.size() < 1)
        return false;

    for(size_t c = 0; c < bitStream.size(); c++)
    {
        // if value is 0, go left
        if(bitStream[c] == 0)
        {
            if(currentNode->_left != NULL)
            {
                currentNode = currentNode->_left;
            }
            else
            {
                return false;
            }
        }
        else if(bitStream[c] == 1)
        {
            if(currentNode->_right != NULL)
            {
                currentNode = currentNode->_right;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    if(currentNode->_nodeType == leaf)
    {
        symbol = currentNode->_data;
        return true;
    }
    else
    {
        return false;
    }
}
