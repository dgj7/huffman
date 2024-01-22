#ifndef __HUFFMAN__CODING__DG__H__
#define __HUFFMAN__CODING__DG__H__

class HNode
{
public:
	HNode( __datatype );

	HNode operator++(  );		// prefix
	HNode operator++( int );	// postfix


	__datatype _symbol;
	ulint _frequency;
};





#endif
