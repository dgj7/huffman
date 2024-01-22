


#ifndef __HUFFMAN__TREE__DG__H__
#define __HUFFMAN__TREE__DG__H__

#include <vector>
#include <string>
#include <list>
#include <utility>
#include <map>

enum NodeType
{
	leaf,
	internal
};

class HNode
{
public:
	HNode(  );		// dont give any values; used for copy_tree

public:
	uint8_t _data;
	uint64_t _freq;
	HNode *_left;
	HNode *_right;
	NodeType _nodetype;
};

class HTree
{
friend bool operator<( HTree, HTree );
public:
	HTree( uint8_t data, uint64_t freq );		// tree with one node
	HTree( HTree, HTree );		// combining internal trees
	HTree(  );
	HTree( const HTree & );		// copy constructor
	virtual ~HTree(  );			// destructor

	uint64_t get_frequency(  ) const;

	HTree &operator=( const HTree & );

public:
	HNode *_root;

private:
	void p_print_contents_inorder( HNode * ) const;
	void p_kill_tree( HNode *& );
	void p_print_codes( HNode *node, bool preDirection, bool path[], uint64_t pathlen );
};

// functions
void copy_tree( HNode *&copyTo, HNode *copyFrom );

// build new huffman tree from given input
HTree build_huffman_tree( std::string );
HTree build_huffman_tree( std::map<uint8_t, uint64_t> );
HTree build_huffman_tree( std::list<HTree> );

// get the bits for a given input symbol
std::vector<bool> get_code( uint8_t, HTree );
void get_code_helper( uint8_t, HNode *, HNode *, bool, bool path[], uint64_t, std::vector<bool> & );

// get the symbol for the given input bits, if one exists
bool get_symbol( std::vector<bool>, uint8_t &, HTree );

// encode a string using the given tree
std::vector<bool> huffman_encode( std::string, HTree );

// decode a bit stream using the given tree
std::string huffman_decode( std::vector<bool>, HTree );

// convert a string to a bit stream, or vice versa
std::vector<bool> string_to_bits( std::string );
std::string bits_to_string( std::vector<bool> );

// generate various lists of frequencies
std::map<uint8_t, uint64_t> generate_frequency_map( std::string );


// "fix" frequency list for purpose of efficient serialization


#endif
