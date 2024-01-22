#include "htree.h"

//==============================================================================
// functions
//==============================================================================
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

bool operator<( HTree left, HTree right )
{
	ulint l = left.get_frequency(  );
	ulint r = right.get_frequency(  );
	
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
	copy_tree( _root->_right, righttree._root );
}

HTree::HTree(  )
{// unparameterized constructor ensures compatibility with std::list<T>
	_root = NULL;
}

HTree::~HTree(  )
{
	p_kill_tree( _root );
}
	
void HTree::p_kill_tree( HNode *&node )
{
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

std::vector<bool> get_code( uint8_t code, HTree tree )
{
	bool path[65535];	// max size of wide char
	std::vector<bool> retval;
	
	retval.clear(  );
	get_code_helper( code, tree._root, 0, path, 0, retval );
	
	return retval;
}

void get_code_helper( uint8_t code, HNode *node, bool preDirection, bool path[], uint64_t pathLen, std::vector<bool> &ret )
{
	if( node == NULL )
		return;
	
	if( node == _root )
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
				retval.push_back( path[c] );
			}
		}
	}
	else
	{
		get_code_helper( code, node->_left, 0, path, pathLen, ret );
		get_code_helper( code, node->_right, 1, path, pathLen, ret );
	}
}
	
	
	
	