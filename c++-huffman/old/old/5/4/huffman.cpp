#include "huffman.h"

////===========================================================================
////		TREE MEMBER FUNCTIONS
////===========================================================================

HTree::HTree( __datatype &data, ulint frequency )
{
	_root = new HLeaf( data, frequency );
}

HTree::HTree( HTree *left, HTree *right )
{
	_root = new HIntl( left->getRoot(  ), right->getRoot(  ) );
}

HTree::~HTree(  )
{
	delete _root;
}

HNode *HTree::getRoot(  )
{
	return _root;
}

ulint HTree::weight(  )
{
	return this->_root->weight(  );
}

////===========================================================================
////		NODE MEMBER FUNCTIONS -- for leaf and internal nodes
////===========================================================================

HLeaf::HLeaf( const __datatype &data, ulint frequency )
{
	_data = new FrequencyPair( data, frequency );
}

HLeaf::~HLeaf(  )
{
	delete _data;
}

ulint HLeaf::weight(  )
{
	return this->_data->weight(  );
}

FrequencyPair *HLeaf::getPair(  )
{
	return _data;
}

bool HLeaf::isLeaf(  )
{
	return true;
}

HNode *HLeaf::left(  ) const
{
	return NULL;
}

HNode *HLeaf::right(  ) const
{
	return NULL;
}

void HLeaf::setLeft( HNode *left )
{
	//
}

void HLeaf::setRight( HNode *right )
{
	//
}




HIntl::HIntl( HNode *left, HNode *right )
 : _left( left ), _right( right )
{
	_frequency = left->weight(  ) + right->weight(  );
}

ulint HIntl::weight(  )
{
	return _frequency;
}

bool HIntl::isLeaf(  )
{
	return false;
}

HNode *HIntl::left(  ) const
{
	return _left;
}

HNode *HIntl::right(  ) const
{
	return _right;
}

void HIntl::setLeft( HNode *left )
{
	_left = (HNode *)left;
}

void HIntl::setRight( HNode *right )
{
	_right = (HNode *)right;
}

////===========================================================================
////		FREQUENCY PAIR MEMBER FUNCTIONS
////===========================================================================

FrequencyPair::FrequencyPair( const __datatype &data, ulint frequency )
 : _data( data ), _freq( frequency )
{
	//
}

FrequencyPair::~FrequencyPair(  )
{
	//
}

ulint FrequencyPair::weight(  )
{
	return this->_freq;
}

__datatype &FrequencyPair::getData(  )
{
	return this->_data;
}

////===========================================================================
////		HUFFMAN LIST MEMBER FUNCTIONS
////===========================================================================

HList::HList(  )
{
	//
}

void HList::push( __datatype data, ulint frequency )
{
	HTree target( data, frequency );

	if( !_hfl.empty(  ) )
	{
		std::list<HTree>::iterator pos = _hfl.begin(  );

		HTree temp( *pos->getRoot(  )->
	}
	else
	{
		_hfl.push_back( target );
	}
}
