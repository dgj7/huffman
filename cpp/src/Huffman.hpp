#ifndef __HUFFMAN__TREE__H__
#define __HUFFMAN__TREE__H__

#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdint.h>

namespace huffman {
	enum NodeType
	{
		leaf,
		internal
	};

	class Node
	{
	public:
		Node();

		uint64_t size() const;
	public:
		uint8_t _data;
		uint64_t _freq;
		Node *_left;
		Node *_right;
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
		Node *_root;
	private:
		void killTree(Node *&);
		void copyTree(Node *&copyTo, Node *copyFrom);		// copy one node to another
	};


	namespace builder {
		HuffmanTree build(std::string);									// build from frequencies in a string
		HuffmanTree build(std::map<uint8_t,uint64_t>);					// build from given frequency set
		HuffmanTree build(std::list<HuffmanTree>);						// build from a list of smaller trees
	}


	namespace encoder {
		std::vector<bool> encode(std::string, HuffmanTree);
	}


	namespace decoder {
		std::string decode(std::vector<bool>, HuffmanTree);
	}
}

#endif
