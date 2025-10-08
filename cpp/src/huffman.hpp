#ifndef HUFFMAN__TREE__H__
#define HUFFMAN__TREE__H__

#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdint.h>

/**
 * <p>
 * Main namespace for everything huffman-related.
 * </p>
 */
namespace huffman {
	/**
	 * Enumeration of node types.
	 */
	enum NodeType
	{
		leaf,
		internal
	};

	/**
	 * <p>
	 * Node type, on which the tree is based.
	 * </p>
	 */
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

	/**
	 * <p>
	 * Huffman binary tree, based on {@link Node}.
	 * </p>
	 */
	class Tree
	{
	friend bool operator<(Tree, Tree);
	public:
		Tree(uint8_t data, uint64_t freq);				// tree with one node
		Tree(Tree, Tree);								// combining internal trees
		Tree();											// no args constructor
		Tree(const Tree &);								// copy constructor
		virtual ~Tree();
		
		uint64_t getFrequency() const;					// read frequency
		Tree &operator=(const Tree &);					// assignment
		uint64_t size() const;							// number of elements in the tree
	public:
		Node *_root;
	private:
		void killTree(Node *&);
		void copyTree(Node *&copyTo, Node *copyFrom);	// copy one node to another
	};

	/**
	 * Builder utility.
	 */
	namespace builder {
		Tree build(std::string);						// build from frequencies in a string
		Tree build(std::map<uint8_t,uint64_t>);			// build from given frequency set
		Tree build(std::list<Tree>);					// build from a list of smaller trees
	}

	/**
	 * Encoder utility.
	 */
	namespace encoder {
		std::vector<bool> encode(std::string, Tree);
	}

	/**
	 * Decoder utility.
	 */
	namespace decoder {
		std::string decode(std::vector<bool>, Tree);
	}
}

#endif
