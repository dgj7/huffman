/*******************************************************************************
		HUFFMAN CODING TREE
	PURPOSE:	Implementation of the Huffman Coding Tree algorithm.
			Uses a special binary tree built from the bottom-up
			using frequency of the bytes being compressed to
			determine how to store each byte most efficiently.
			More info: http://en.wikipedia.org/wiki/Huffman_coding
	PROGRAMMER:	David Garcia Jr, dagarcia@umflint.edu
	START DATE:	December 2007; This rewrite started on 10/5/2009
	FILENAME:	htree.h
*******************************************************************************/
// NEED ASSIGNMENT OPERATOR AND DESTRUCTOR!!!!!!!!
#ifndef __HUFFMAN__CODING__TREE__DG__H__
#define __HUFFMAN__CODING__TREE__DG__H__

typedef unsigned long int ulint;	// in case we decide to change int type
typedef char Data;			// in case we decide to change datatype

enum NodeType
{
	leaf,
	internal
};

class HNode
{
public:
	// variables
	Data _data;
	ulint _frequency;
	HNode *_left;
	HNode *_right;
	NodeType _nodetype;
	
	// functions
	//HNode( HNode *, HNode *, ulint, NodeType = internal );	// for internal nodes
	//HNode( Data, ulint, NodeType = leaf );		// for leaf nodes
	HNode(  );	// dont give any values; for copy_bst
};

class HTree
{
friend void copy_tree( HNode *&, HNode * );
public:
	HTree( Data, ulint );			// for tree with one node
	HTree( HTree, HTree );			// for combining trees, ie internal
	HTree(  );
	HTree( const HTree & );			// copy constructor
	
	ulint get_frequency(  ) const;
	
	// debug function!
	void print_contents_inorder(  ) const;

private:
	HNode *_root;
	
	void p_print_contents_inorder( HNode * ) const;
};

#endif
