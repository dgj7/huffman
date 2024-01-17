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
	
	void setOriginal(std::string);
	std::string getOriginal() const;
	
public:
	HuffmanNode *_root;
	
private:
	void killTree(HuffmanNode *&);
	void copyTree(HuffmanNode *&copyTo, HuffmanNode *copyFrom);		// copy one node to another
	
	std::string original;
};

class HuffmanTreeBuilder
{
public:
	HuffmanTreeBuilder();
	virtual ~HuffmanTreeBuilder();

	HuffmanTree build(std::string);									// build from frequencies in a string
	HuffmanTree build(std::map<uint8_t,uint64_t>);					// build from given frequency set
	HuffmanTree build(std::list<HuffmanTree>);						// build from a list of smaller trees
	HuffmanTree buildStandardFrequencyTree();
};

class HuffmanEncoder
{
public:
	std::vector<bool> getCode(uint8_t, HuffmanTree);
	std::vector<bool> encode(std::string, HuffmanTree);
	std::vector<bool> stringToBits(std::string);
	std::map<uint8_t,uint64_t> generateFrequencyMap(std::string);
	uint64_t getFrequency(std::string, char);
private:
	void getCodeHelper(uint8_t, HuffmanNode *, HuffmanNode *, bool, bool path[], uint64_t, std::vector<bool> &);
};

class HuffmanDecoder
{
public:
	bool getSymbol(std::vector<bool>, uint8_t &, HuffmanTree);
	std::string decode(std::vector<bool>, HuffmanTree);
	std::string bitsToString(std::vector<bool>);
};

class HuffmanConsolePrinter
{
public:
	void printContentsInorder(HuffmanNode *) const;
	void printCodes(HuffmanTree);
	std::string getUniqueSymbols(std::string);
private:
	HuffmanEncoder encoder;
};

#endif
