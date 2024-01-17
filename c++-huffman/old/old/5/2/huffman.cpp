#include "huffman.h"

// postfix increment operator overloaded
HNode HNode::operator++( int ignore )
{
	ulint temp = _frequency;
	_frequency++;



// eof
