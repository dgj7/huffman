#include "htree.h"

#include <bitset>

// temporary
#include <iostream>

//==============================================================================
// node
//==============================================================================
HNode::HNode(  )
{
	_left = NULL;
	_right = NULL;
}

//==============================================================================
// tree
//==============================================================================
HTree::HTree( uint8_t data, uint64_t freq )
{	// leaf trees
	_root = new HNode(  );
	_root->_nodetype = leaf;
	_root->_data = data;
	_root->_freq = freq;
	_root->_left = NULL;
	_root->_right = NULL;
}

HTree::HTree( HTree leftTree, HTree rightTree )
{	// combine trees
	_root = new HNode(  );

	_root->_freq = leftTree.get_frequency(  ) + rightTree.get_frequency(  );
	_root->_nodetype = internal;

	copy_tree( _root->_left, leftTree._root );
	copy_tree( _root->_right, rightTree._root );
}

HTree::HTree(  )
{// unparameterized constructor ensures compatibility with std::list<T>
	_root = NULL;
}

HTree::HTree( const HTree &copyFrom )
{   // copy constructor
    copy_tree( _root, copyFrom._root );
}

HTree::~HTree(  )
{
	p_kill_tree( _root );
}

void HTree::p_kill_tree( HNode *&node )
{
    if( node == NULL ) return;

	if( node->_left != NULL )
		p_kill_tree( node->_left );

	if( node->_right != NULL )
		p_kill_tree( node->_right );

	if( node->_left != NULL )
	{
		delete node->_left;
		node->_left = NULL;
	}

	if( node->_right != NULL )
	{
		delete node->_right;
		node->_right = NULL;
	}
}

uint64_t HTree::get_frequency(  ) const
{
	return _root->_freq;
}

HTree &HTree::operator=( const HTree &copyFrom )
{
	if( this != &copyFrom )
	{
		p_kill_tree( _root );
		copy_tree( _root, copyFrom._root );
	}
	return *this;
}

bool operator<( HTree left, HTree right )
{
	uint64_t l = left.get_frequency(  );
	uint64_t r = right.get_frequency(  );

	if( l < r )
	{
		return true;
	}
	// if the frequencies are equal
	else if( l == r )
	{
		// if both left and right are internals, leave them alone
		if( left._root->_nodetype != leaf && right._root->_nodetype != leaf )
		{
			return true;
			// effectively leave it alone if it's an internal and the frequencies are equal
		}
		// if only one of the two is a leaf, the leaf is less than the internal
		else if( left._root->_nodetype == leaf && right._root->_nodetype != leaf )
		{
			return true;
		}
		else if( right._root->_nodetype == leaf && left._root->_nodetype != leaf )
		{
			return false;
		}
		// if left and right are both leaves, compare the data
		else if( left._root->_data < right._root->_data )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// frequencies arent less than or equal to... so greater than
	else
	{
		return false;
	}
}

//==============================================================================
// functions
//==============================================================================
HTree build_huffman_tree( std::string input )
{
    std::map<uint8_t,uint64_t> frequencies;
    for( size_t c = 0; c < input.size(  ); c++ )
    {
        if( frequencies.find(input[c]) == frequencies.end(  ) )
        {   // if it's not in the list, add it
            frequencies[input[c]] = 1;
        }
        else
        {
            frequencies[input[c]] += 1;
        }
    }

    return build_huffman_tree( frequencies );
}

HTree build_huffman_tree( std::map<uint8_t, uint64_t> freq )
{
    HTree retTree;

    std::list<HTree> treeList;
    std::map<uint8_t,uint64_t>::iterator it = freq.begin(  );


    while( it != freq.end(  ) )
    {
        //std::cout << "\nfirst: " << it->first << "\t,\t" << it->second;
        HTree tempTree( it->first, it->second );
        treeList.push_back( tempTree );
        it++;
    }

    return build_huffman_tree( treeList );
}

HTree build_huffman_tree( std::list<HTree> trees )
{
    trees.sort(  );
    HTree tr;

    while( trees.size(  ) > 1 )
    {
        std::list<HTree>::iterator firstIter = trees.begin(  );
        std::list<HTree>::iterator secondIter = trees.begin(  );
        secondIter++;

        HTree newTree( (*firstIter), (*secondIter) );

        trees.erase( firstIter );
        trees.erase( secondIter );

        trees.push_back( newTree );
        trees.sort(  );

        if( trees.size(  ) == 1 )
        {
            std::list<HTree>::iterator thirdIter = trees.begin(  );
            tr = HTree( *thirdIter );
        }
    }

    return tr;
}

std::vector<bool> huffman_encode( std::string input, HTree tree )
{
    std::vector<bool> bits;

    // add 3 bits on front, to store the amount of padding needed (most is 7, or 1+2+4
    bits.push_back( 0 );
    bits.push_back( 0 );
    bits.push_back( 0 );

    for( size_t c = 0; c < input.size(  ); c++ )
    {
        char current = input[c];
        std::vector<bool> letterCode = get_code( current, tree );
        if( letterCode.size(  ) > 0 )
        {
            for( size_t d =0; d < letterCode.size(  ); d++ )
            {
                bits.push_back( letterCode[d] );
            }
        }
    }

    // how many bits do we need to add to the end?
    short padding = 8 - ( bits.size(  ) % 8 );
    std::cout << "\nsize is " << bits.size(  ) << ", padding=" << padding << "\n";
    for( short d = 0; d < padding; d++ )
        bits.push_back( 0 );
    std::bitset<3> pad = padding;
    bits[0] = pad[0];
    bits[1] = pad[1];
    bits[2] = pad[2];

    return bits;
}

std::string huffman_decode( std::vector<bool> bitStream, HTree tree )
{
    std::string ret = "";
    //std::vector<bool> bitStreamWithoutPadding = bitStream;

    // compensate for the padding that is now in front
    short padding = bitStream[0] * 1 + bitStream[1] * 2 + bitStream[2] * 4;

    std::vector<bool> bitStreamWithoutPadding;
    for( size_t x = 3; x < bitStream.size(  ) - padding; x++ )
        bitStreamWithoutPadding.push_back( bitStream[x] );

    // algorithm:
    // one bit at a time, pass as a code to get_symbol
    // if the current bit stream isnt a code, add the next
    // bit and try again.
    // when it is a code, remove those from the main bitstream and start over
    // also add the found code to the return string
    while( bitStreamWithoutPadding.size(  ) > 0 )
    {
        bool haveCode = false;
        size_t ct = 0;
        uint8_t letter;
        while( !haveCode )
        {
            std::vector<bool> bits;
            for( size_t c = 0; c < ct; c++ )
            {
                bits.push_back( bitStreamWithoutPadding[c] );
            }

            haveCode = get_symbol( bits, letter, tree );

            ct++;
        }

        ret += char(letter);

        // now erase the first ct elements from bitStream
        ct--;
        //std::cout << "\n\tERASING " << ct << " elements from bitStream: oldsize=" << bitStream.size(  );
        bitStreamWithoutPadding.erase( bitStreamWithoutPadding.begin(  ), bitStreamWithoutPadding.begin(  ) + ct );
        //std::cout << ", newsize=" << bitStream.size(  ) << ")";
    }

    return ret;
}

std::vector<bool> get_code( uint8_t code, HTree tree )
{
	bool path[65535];	// max size of wide char
	std::vector<bool> retval;

	retval.clear(  );
	get_code_helper( code, tree._root, tree._root, 0, path, 0, retval );

	return retval;
}

void get_code_helper( uint8_t code, HNode *node, HNode *root, bool preDirection, bool path[], uint64_t pathLen, std::vector<bool> &ret )
{
	if( node == NULL )
		return;

	if( node == root )
	{
		// don't do anything, didnt come from left or right
	}
	else
	{
		if( preDirection == 0 )
			path[pathLen] = 0;
		else
			path[pathLen] = 1;

		pathLen++;
	}

	// if it's a leaf node AND it's the one we're looking for, return the data
	if( node->_left == NULL && node->_right == NULL )
	{
		if( node->_data == code )
		{
			for( uint64_t c = 0; c < pathLen; c++ )
			{
				ret.push_back( path[c] );
			}
		}
	}
	else
	{
		get_code_helper( code, node->_left, root, 0, path, pathLen, ret );
		get_code_helper( code, node->_right, root, 1, path, pathLen, ret );
	}
}

bool get_symbol( std::vector<bool> bitStream, uint8_t &symbol, HTree tree )
{
    //std::cout << "\ngetting symbol for bit stream size " << bitStream.size(  ) << ":\t";
    //for( size_t x = 0; x < bitStream.size(  ); x++ ) std::cout << bitStream[x];
    HNode *currentNode = tree._root;

    if( bitStream.size(  ) < 1 )
        return false;

    for( size_t c = 0; c < bitStream.size(  ); c++ )
    {
        // if value is 0, go left
        if( bitStream[c] == 0 )
        {
            //std::cout << "\n\ttrying to go LEFT...";
            if( currentNode->_left != NULL )
            {
                currentNode = currentNode->_left;
            }
            else
            {
                //std::cout << "\n\t\tleft is null!";
                return false;
            }
        }
        // if value is 1, go right
        else if( bitStream[c] == 1 )
        {
            //std::cout << "\n\ttrying to go RIGHT...";
            if( currentNode->_right != NULL )
            {
                currentNode = currentNode->_right;
            }
            else
            {
                //std::cout << "\n\t\tright is null!";
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    if( currentNode->_nodetype == leaf )
    {
        symbol = currentNode->_data;
        //std::cout << "\n\tsymbol: " << char( symbol ) << ", " << (int)symbol;
        return true;
    }
    else
    {
        //std::cout << "\n\tno symbol...";
        return false;
    }
}

std::string bits_to_string( std::vector<bool> bits )
{
    std::string text = "";

    while( bits.size(  ) > 0 )
    {
        std::bitset<8> byte;
        for( size_t c = 0; c < 8; c++ )
            byte[c] = bits[c];
        text += char( byte.to_ulong(  ) );
        bits.erase( bits.begin(  ), bits.begin(  ) + 8 );
    }

    return text;
}

std::vector<bool> string_to_bits( std::string text )
{
    std::vector<bool> bits;

    for( size_t c = 0; c < text.size(  ); c++ )
    {
        char ch = text[c];
        std::bitset<8> byte( (short)ch );

        for( size_t bit = 0; bit < byte.size(  ); bit++ )
        {
            bits.push_back( byte[bit] );
        }
    }

    return bits;
}

void copy_tree( HNode *&copyTo, HNode *copyFrom )
{
	if( copyFrom == NULL )
	{
		copyTo = NULL;
	}
	else
	{
		copyTo = new HNode(  );
		copyTo->_freq = copyFrom->_freq;
		copyTo->_data = copyFrom->_data;
		copyTo->_nodetype = copyFrom->_nodetype;

		copy_tree( copyTo->_left, copyFrom->_left );
		copy_tree( copyTo->_right, copyFrom->_right );
	}
}

