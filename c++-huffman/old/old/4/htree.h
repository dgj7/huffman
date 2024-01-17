


#ifndef __HUFFMAN__TREE__DG__H__
#define __HUFFMAN__TREE__DG__H__

#include <vector>
#include <string>
#include <list>
#include <utility>

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

HTree build_huffman_tree( std::list<HTree> );
HTree build_huffman_tree( std::vector< std::pair< uint8_t, uint64_t > > );
HTree build_huffman_tree( std::string );

std::vector<bool> get_code( uint8_t symbol );

#endif
