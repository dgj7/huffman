#ifndef __HUFFMAN__TREE__H__
#define __HUFFMAN__TREE__H__

#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdint.h>

enum NodeType
{
	leaf,
	internal
};

class HuffmanNode
{
public:
	HuffmanNode();

	uint64_t size() const;
public:
	uint8_t _data;
	uint64_t _freq;
	HuffmanNode *_left;
	HuffmanNode *_right;
	NodeType _nodeType;
};

class HuffmanTree
{
friend bool operator<(HuffmanTree, HuffmanTree);
public:
	HuffmanTree(uint8_t data, uint64_t freq);						// tree with one node
	HuffmanTree(HuffmanTree, HuffmanTree);							// combining internal trees
	HuffmanTree();													// no args constructor
	HuffmanTree(const HuffmanTree &);								// copy constructor
	virtual ~HuffmanTree();
	
	uint64_t getFrequency() const;									// read frequency
	HuffmanTree &operator=(const HuffmanTree &);					// assignment
	uint64_t size() const;											// number of elements in the tree
public:
	HuffmanNode *_root;
private:
	void killTree(HuffmanNode *&);
	void copyTree(HuffmanNode *&copyTo, HuffmanNode *copyFrom);		// copy one node to another
};

class HuffmanTreeBuilder
{
public:
	HuffmanTreeBuilder();
	virtual ~HuffmanTreeBuilder();

	HuffmanTree build(std::string);									// build from frequencies in a string
	HuffmanTree build(std::map<uint8_t,uint64_t>);					// build from given frequency set
	HuffmanTree build(std::list<HuffmanTree>);						// build from a list of smaller trees
private:
	void sort_list(std::list<HuffmanTree> &);
	void debug_print(std::list<HuffmanTree> &) const;
	std::string debug_find_all_frequency_pairs(HuffmanNode *) const;
};

class HuffmanEncoder
{
public:
	std::vector<bool> getCode(uint8_t, HuffmanTree) const;
	std::vector<bool> encode(std::string, HuffmanTree) const;
private:
	void getCodeHelper(uint8_t, HuffmanNode *, HuffmanNode *, bool, bool path[], uint64_t, std::vector<bool> &) const;
};

class HuffmanDecoder
{
public:
	bool getSymbol(std::vector<bool>, uint8_t &, HuffmanTree) const;
	std::string decode(std::vector<bool>, HuffmanTree) const;
};

#endif
