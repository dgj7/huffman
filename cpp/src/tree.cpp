#include "Huffman.hpp"

namespace huffman {
	HuffmanTree::HuffmanTree(
		uint8_t data, uint64_t freq
	) {	// leaf trees
		_root = new Node();
		_root->_nodeType = leaf;
		_root->_data = data;
		_root->_freq = freq;
		_root->_left = NULL;
		_root->_right = NULL;
	}

	HuffmanTree::HuffmanTree(
		HuffmanTree leftTree,
		HuffmanTree rightTree
	) {
		// combine trees
		_root = new Node();

		_root->_freq = leftTree.getFrequency() + rightTree.getFrequency();
		_root->_nodeType = internal;

		copyTree(_root->_left, leftTree._root);
		copyTree(_root->_right, rightTree._root);
	}

	HuffmanTree::HuffmanTree()
	{// unparameterized constructor ensures compatibility with std::list<T>
		_root = NULL;
	}

	HuffmanTree::HuffmanTree(
		const HuffmanTree &copyFrom
	) {   // copy constructor
		copyTree(_root, copyFrom._root);
	}

	HuffmanTree::~HuffmanTree()
	{
		killTree(_root);
	}

	void
	HuffmanTree::killTree(
		Node *&node
	) {
		if(node == NULL) return;

		if(node->_left != NULL)
			killTree(node->_left);

		if(node->_right != NULL)
			killTree(node->_right);

		if(node->_left != NULL)
		{
			delete node->_left;
			node->_left = NULL;
		}

		if(node->_right != NULL)
		{
			delete node->_right;
			node->_right = NULL;
		}
	}

	uint64_t
	HuffmanTree::getFrequency() const
	{
		return _root->_freq;
	}

	HuffmanTree &
	HuffmanTree::operator=(
		const HuffmanTree &copyFrom
	) {
		if(this != &copyFrom)
		{
			killTree(_root);
			copyTree(_root, copyFrom._root);
		}
		return *this;
	}

	bool
	operator<(
		HuffmanTree left,
		HuffmanTree right
	) {
		uint64_t l = left.getFrequency();
		uint64_t r = right.getFrequency();

		if(l != r)
		{
			return l < r;
		}
		else// if the frequencies are equal
		{
			if (left._root->_nodeType == leaf && right._root->_nodeType == leaf) {
				return left._root->_data < right._root->_data;
			} else {
				return left.size() < right.size();
			}
		}
	}

	uint64_t
	HuffmanTree::size() const {
		return this->_root->size();
	}

	void
	HuffmanTree::copyTree(
		Node *&copyTo,
		Node *copyFrom
	) {
		if(copyFrom == NULL)
		{
			copyTo = NULL;
		}
		else
		{
			copyTo = new Node();
			copyTo->_freq = copyFrom->_freq;
			copyTo->_data = copyFrom->_data;
			copyTo->_nodeType = copyFrom->_nodeType;

			copyTree(copyTo->_left, copyFrom->_left);
			copyTree(copyTo->_right, copyFrom->_right);
		}
	}
}
