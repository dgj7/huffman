#include <stddef.h>		// for NULL
#include <iostream>		// for debug function only!!!

#include "htree.h"

/********************
CONSTRUCTORS, COPY CONSTRUCTOR, COPIER, DESTRUCTOR
********************/
HNode::HNode(  )
{
	//std::cout << "\n\tcalling HNode(  ) unparameterized constructor\n";
	_left = NULL;
	_right = NULL;
}
/*
HNode::HNode( HNode *left, HNode *right, ulint frequency, NodeType nodetype )
{
	_nodetype = nodetype;
	_frequency = frequency;

	copy_tree( _left, left );
	copy_tree( _right, right );
}

HNode::HNode( Data data, ulint frequency, NodeType nodetype )
{
	_nodetype = nodetype;
	_data = data;
	_frequency = frequency;
	_left = NULL;
	_right = NULL;
}
*/
// for trees with just one leaf node
HTree::HTree( Data data, ulint frequency )
{
	//std::cout << "calling HTree( " << data << ", " << frequency << " )...";
	_root = new HNode(  );
	_root->_nodetype = leaf;
	_root->_data = data;
	_root->_frequency = frequency;
	_root->_left = NULL;
	_root->_right = NULL;
}

// for trees with multiple nodes, ie combining trees
HTree::HTree( HTree lefttree, HTree righttree )
{
	//std::cout << "calling HTree( HTree, HTree ) with HTree( "
	//	  << lefttree.get_frequency(  ) << ", "
	//	  << righttree.get_frequency(  ) << " )\n";

	_root = new HNode(  );
	
	_root->_frequency = lefttree.get_frequency(  ) + righttree.get_frequency(  );
	_root->_nodetype = internal;
	
	copy_tree( _root->_left, lefttree._root );
	copy_tree( _root->_right, righttree._root );
}

// unparameterized constructor to ensure compatibility with std::list
HTree::HTree(  )
{
	_root = NULL;
}

// copy constructor
HTree::HTree( const HTree &copyFrom )
{
	//std::cout << "calling copy contructor.\n";
	copy_tree( _root, copyFrom._root );
}

void copy_tree( HNode *&copyTo, HNode *copyFrom )
{
	//std::cout << "calling copy_tree(  )\n";
	if( copyFrom == NULL )
	{
		copyTo = NULL;
	}
	else
	{
		copyTo = new HNode(  );
		copyTo->_frequency = copyFrom->_frequency;
		copyTo->_data = copyFrom->_data;
		copyTo->_nodetype = copyFrom->_nodetype;
		
		copy_tree( copyTo->_left, copyFrom->_left );
		copy_tree( copyTo->_right, copyFrom->_right );
	}
}

/********************
huh?
********************/

ulint HTree::get_frequency(  ) const
{
	//std::cout << "calling get_frequency(  )\n";
	return _root->_frequency;
}

void HTree::print_contents_inorder(  ) const
{
	//std::cout << "\ncalling print_contents_inorder(  )";
	p_print_contents_inorder( _root );
}

void HTree::p_print_contents_inorder( HNode *pointer ) const
{
	//std::cout << "calling p_print_contents_inorder(  )";
	if( pointer != NULL )
	{
		p_print_contents_inorder( pointer->_left );
	
		if( pointer->_nodetype == internal )
		{
			std::cout << "\n\t[ internal ]\t[]\t["
				  << pointer->_frequency << "]";
		}
		else
		{
			std::cout << "\n\t[   leaf   ]\t["
				  << pointer->_data << "]\t["
				  << pointer->_frequency << "]";
		}
		
		p_print_contents_inorder( pointer->_right );
	}
}




