#include "huffman.hpp"

/**
 * Huffman coding tree.
 */
namespace huffman {
	/**
	 * Tree constructor, from single byte and frequency.
	 */
	Tree::Tree(
		const uint8_t data,
		const uint64_t freq
	) {
		_root = new Node();
		_root->_nodeType = leaf;
		_root->_data = data;
		_root->_freq = freq;
		_root->_left = NULL;
		_root->_right = NULL;
	}

	/**
	 * Tree constructor, from two child trees.
	 */
	Tree::Tree(
		const Tree & leftTree,
		const Tree & rightTree
	) {
		_root = new Node();

		_root->_freq = leftTree.getFrequency() + rightTree.getFrequency();
		_root->_nodeType = internal;

		copyTree(_root->_left, leftTree._root);
		copyTree(_root->_right, rightTree._root);
	}

	/**
	 * Tree constructor, unparameterized for compatability with std::list.
	 */
	Tree::Tree()
	{
		_root = NULL;
	}

	/**
	 * Tree copy constructor.
	 */
	Tree::Tree(
		const Tree &copyFrom
	) {   // copy constructor
		copyTree(_root, copyFrom._root);
	}

	/**
	 * Tree destructor.
	 */
	Tree::~Tree()
	{
		killTree(_root);
	}

	/**
	 * helper/private method to delete a tree and free it's memory.
	 */
	void
	Tree::killTree(
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

	/**
	 * frequency accessor.
	 */
	uint64_t
	Tree::getFrequency() const
	{
		return _root->_freq;
	}

	/**
	 * Assignment operator overloaded.
	 */
	Tree &
	Tree::operator=(
		const Tree &copyFrom
	) {
		if(this != &copyFrom)
		{
			killTree(_root);
			copyTree(_root, copyFrom._root);
		}
		return *this;
	}

	/**
	 * Less-than operator overloaded.
	 */
	bool
	operator<(
		const Tree & left,
		const Tree & right
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

	/**
	 * Size accessor.
	 */
	uint64_t
	Tree::size() const {
		if (this->_root == nullptr)
		{
			return 0;
		}
		else
		{
			return this->_root->size();
		}
	}

	/**
	 * Tree copy helper method.
	 */
	void
	Tree::copyTree(
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
