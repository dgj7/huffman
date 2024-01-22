/******************************************************************************
	HUFFMAN CODING TREE
	-------------------
	FILE: 		htree.h
	PURPOSE: 	interface for HuffmanTree class
	
	DATE: v1: December 2007
		  v2: 10/5/2009
		  v3: 2/8/2010 - x
	PROGRAMMER: David Garcia Jr, dagarcia@umflint.edu
******************************************************************************/
#ifndef __HUFFMAN__CODING__TREE__DG__H__
#define __HUFFMAN__CODING__TREE__DG__H__

#include <list>
#include <utility>
#include <vector>
#include <fstream>

// These typedefs make it easier to change the types being used at a later date
typedef unsigned long int ulint;	// frequency of a symbol
typedef char Data;					// data being stored; ie, the symbol
typedef std::string stringtype;		// in case i want to change to wchar_t later

// is the node a leaf or an internal?
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
	
	// constructor
	HNode(  );		// dont give any values; used for copy_bst
};

class HTree
{
friend class HuffmanCompress;
friend class HuffmanDecompress;
friend void copy_tree( HNode *&, HNode * );
friend bool operator<( HTree, HTree );
public:
	HTree( Data, ulint );	// for tree with one node
	HTree( HTree, HTree );	// for combining trees, ie internal
	HTree(  );
	HTree( const HTree & );	// copy constructor
	virtual ~HTree(  );		// destructor
	
	ulint get_frequency(  ) const;
	
	HTree &operator=( const HTree & );
	
	// debug functions!!!
	void print_contents_inorder(  ) const;
	void print_codes(  );		// use root-to-node algo to print the codes in the tree
	
private:
	HNode *_root;
	
	void p_print_contents_inorder( HNode * ) const;
	void p_kill_tree( HNode *& );
	void p_print_codes( HNode *node, bool preDirection, bool path[], ulint pathlen );
};	

class HuffmanCompress
{
public:
	HuffmanCompress( stringtype );

	bool get_code_for_symbol( Data, std::vector< bool > & );
	
	// debug
	//void debug_print_vector(  ) const;

private:
	// change these two from member vars to local constructor vars
	std::list<HTree> _htlist;
	std::vector< std::pair< Data, ulint > > _freqdata;
	
	// data members
	std::vector< std::pair< Data, std::vector< bool > > > _codes;
	HTree *_finalTree;
	
	// helpers
	bool p_find_char_in_frequency_vector( Data, size_t & );
	void p_write_codes( HNode *node, bool preDirection, bool path[], ulint pathLen );
	
	//void p_debug_print_codes_vector(  ) const;
};

#endif
