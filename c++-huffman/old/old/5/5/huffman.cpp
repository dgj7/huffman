#include "huffman.h"


////===========================================================================
////		NODE MEMBER FUNCTIONS
////===========================================================================
/**************************************
	Node constructors
**************************************/
HNode::HNode( ulint weight, __datatype data )
 : _weight( weight ), _data( data ), _parent( 0 ), _left( 0 ), _right( 0 ), leaf( true )
{
	//
}

HNode::HNode( ulint weight )
 : _weight( weight ), _parent( 0 ), _left( 0 ), _right( 0 ), leaf( false )
{
	//
}



////===========================================================================
////		TREE MEMBER FUNCTIONS
////===========================================================================
/**************************************
	Tree constructor
**************************************/
HTree::HTree( HNode input )
{
	_root->_weight = input._weight;
	_root->leaf = input.leaf;
	if( this->_root->leaf )
		_root->_data = input._data;
}

////===========================================================================
////		LIST MEMBER FUNCTIONS
////===========================================================================

void HList::push( ulint weight, __datatype data )
{
	HNode nodetemp( weight, data );
	HTree input( nodetemp );

	if( !_hfl.empty(  ) )
	{
		//
	}
	else
	{
		_hfl.push_back( input );
	}
}

size_t HList::size(  ) const
{
	return _hfl.size(  );
}

