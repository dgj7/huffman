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
// NEED ASSIGNMENT OPERATOR!!!!!!!!
#ifndef __HUFFMAN__CODING__TREE__DG__H__
#define __HUFFMAN__CODING__TREE__DG__H__

#include <list>
#include <utility>
#include <vector>
#include <fstream>

#include "common.h"

typedef unsigned long int ulint;	// in case we decide to change int type
typedef char Data;			// in case we decide to change datatype
typedef std::string stringtype;		// in case we need to change to wstring later
//ulint maxxSymbols = 256;

// function prototypes
inline char *addr( void *ptr );

// is the node a leaf or an internal?
enum NodeType
{
	leaf,
	internal
};

// doing compression or decompression?
enum TreeType
{
	compress,
	decompress
};

// what sort of data are we compressing?
enum DataType
{
	compressString,
	compressFile
};

// how to read data in from the datafile, in the case that DataType == compressFile
struct DataFormat
{
	char c;
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
	HNode(  );	// dont give any values; for copy_bst
};

class HTree
{
friend class HuffmanTree;
friend void copy_tree( HNode *&, HNode * );
friend bool operator<( HTree, HTree );
public:
	HTree( Data, ulint );			// for tree with one node
	HTree( HTree, HTree );			// for combining trees, ie internal
	HTree(  );
	HTree( const HTree & );			// copy constructor
	~HTree(  );				// destructor
	
	ulint get_frequency(  ) const;
	
	HTree &operator=( const HTree & );
	
	// debug functions!
	void print_contents_inorder(  ) const;
	void print_codes(  );		// use root-to-node algo to print the codes in the tree!
 
private:
	HNode *_root;
	
	void p_print_contents_inorder( HNode * ) const;
	void p_kill_tree( HNode *& );
	void p_print_codes( HNode *node, bool preDirection, bool path[], ulint pathLen );
};

// this class is the outside interface!
class HuffmanTree
{
public:
	HuffmanTree( stringtype, DataType, TreeType=compress );
	//HuffmanTree( std::ifstream &, TreeType=compress );

	bool get_code_for_symbol( Data, std::vector< bool > & );
	
	// for debug only
	void debug_print_vector(  ) const;
private:
	// change these two from member vars to local constructor variables
	std::list<HTree> _htlist;
	std::vector< std::pair< Data, ulint > > _freqdata;
	
	// data members
	std::vector< std::pair< Data, std::vector< bool > > > _codes;
	HTree *_finalTree;
	
	bool p_find_char_in_vector( Data, size_t & );
	void p_write_codes( HNode *node, bool preDirection, bool path[], ulint pathLen );
	
	void p_debug_print_codes_vector(  ) const;
};

#endif
