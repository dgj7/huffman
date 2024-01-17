#ifndef __H__TREE__DG__H__
#define __H__TREE__DG__H__

//=============================================================================
//                               CLASS DECLARATIONS
//=============================================================================

template<class _type>
class HNode
{
public:
	bool _isLeaf;
	long _frequency;
	HNode *_left;
	HNode *_right;
	_type _data;
	
	HNode( _type data, long frequency, bool isleaf );		// leaf node
	HNode( long frequency, bool isleaf );				// internal node
	
	
	~HNode(  );
};

template<class _type>
class HTree
{
private:
	HNode<_type> *_root;

public:
	HTree( _type data, long frequency, bool isleaf );		// for an empty tree
	HTree( HTree<_type> *leftTree, HTree<_type> *rightTree );	// for tree that already has data in it
	
	~HTree(  );
	
	HTree( const HTree &h );					// copy constructor
};


//=============================================================================
//                           FUNCTION IMPLEMENTATIONS
//=============================================================================

// HNODE FUNCTIONS

// constructor for leaf nodes
template<class _type>
HNode<_type>::HNode( _type data, long frequency, bool isleaf )
 : _isLeaf( isleaf ), _frequency( frequency ), _left( NULL ), _right( NULL ), _data( data )
{
	std::cout << "created new HNode[leaf] with the value " << 
}

// constructor for internal nodes
template<class _type>
HNode<_type>::HNode( long frequency, bool isleaf )
 : _isLeaf( isleaf ), _frequency( frequency ), _left( NULL ), _right( NULL )
{
	//
}

// HTREE FUNCTIONS

// constructor for an EMPTY tree
template<class _type>
HTree<_type>::HTree( _type data, long frequency, bool isleaf = true )
{
	_root = new HNode<_type>( data, frequency );
}

#endif
