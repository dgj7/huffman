// all the required code to build a huffman coding tree
//==============================================================================
#ifndef __HUFFMAN__CODING__TREE__DG__H__
#define __HUFFMAN__CODING__TREE__DG__H__

#define HTDEBUG

#include <vector>

typedef unsigned long int ulint;


class HNode
{
public:
	virtual ulint weight(  ) = 0;
	virtual bool is_leaf(  ) = 0;

};

class HLeaf: public HNode
{
public:
	HLeaf( char data, ulint freq ) :_data( data ), _frequency( freq ) {}
	ulint weight(  );
	bool is_leaf(  );
	
	char _data;
	ulint _frequency;
	
};

class HIntl: public HNode
{
public:
	HIntl( ulint freq );
	ulint weight(  );
	bool is_leaf(  );
	
	ulint _frequency;
};

class HuffmanTree
{
public:
	HuffmanTree( char data, ulint freq );
	HuffmanTree( HuffmanTree *left, HuffmanTree *right );
	ulint weight(  );
	
	HNode *_root;
};

class HList
{
public:
	HList(  );
	void insert( char input )
	{
		// if the tree is empty, just put the item in the list
		if( _list.empty(  ) )
		{
			HLeaf temp( input, 1 );
			_list.push_back( temp );
		}
	}
	bool find( char );
	
	std::vector<HLeaf> _list;
};





#endif
