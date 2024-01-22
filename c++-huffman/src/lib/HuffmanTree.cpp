#include "Huffman.hpp"

HuffmanTree::HuffmanTree(uint8_t data, uint64_t freq)
{	// leaf trees
	_root = new HuffmanNode();
	_root->_nodeType = leaf;
	_root->_data = data;
	_root->_freq = freq;
	_root->_left = NULL;
	_root->_right = NULL;
}

HuffmanTree::HuffmanTree(HuffmanTree leftTree, HuffmanTree rightTree)
{	// combine trees
	_root = new HuffmanNode();

	_root->_freq = leftTree.getFrequency() + rightTree.getFrequency();
	_root->_nodeType = internal;

	copyTree(_root->_left, leftTree._root);
	copyTree(_root->_right, rightTree._root);
}

HuffmanTree::HuffmanTree()
{// unparameterized constructor ensures compatibility with std::list<T>
	_root = NULL;
}

HuffmanTree::HuffmanTree(const HuffmanTree &copyFrom)
{   // copy constructor
    copyTree(_root, copyFrom._root);
	original = copyFrom.getOriginal();
}

HuffmanTree::~HuffmanTree()
{
	killTree(_root);
}

void HuffmanTree::killTree(HuffmanNode *&node)
{
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

uint64_t HuffmanTree::getFrequency() const
{
	return _root->_freq;
}

HuffmanTree &HuffmanTree::operator=(const HuffmanTree &copyFrom)
{
	if(this != &copyFrom)
	{
		killTree(_root);
		copyTree(_root, copyFrom._root);
		original = copyFrom.getOriginal();
	}
	return *this;
}

bool operator<(HuffmanTree left, HuffmanTree right)
{
	uint64_t l = left.getFrequency();
	uint64_t r = right.getFrequency();

	if(l < r)
	{
		return true;
	}
	// if the frequencies are equal
	else if(l == r)
	{
		// if both left and right are internals, leave them alone
		if(left._root->_nodeType != leaf && right._root->_nodeType != leaf)
		{
			return true;
			// effectively leave it alone if it's an internal and the frequencies are equal
		}
		// if only one of the two is a leaf, the leaf is less than the internal
		else if(left._root->_nodeType == leaf && right._root->_nodeType != leaf)
		{
			return true;
		}
		else if(right._root->_nodeType == leaf && left._root->_nodeType != leaf)
		{
			return false;
		}
		// if left and right are both leaves, compare the data
		else if(left._root->_data < right._root->_data)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// frequencies arent less than or equal to... so greater than
	else
	{
		return false;
	}
}

void HuffmanTree::copyTree(HuffmanNode *&copyTo, HuffmanNode *copyFrom)
{
	if(copyFrom == NULL)
	{
		copyTo = NULL;
	}
	else
	{
		copyTo = new HuffmanNode();
		copyTo->_freq = copyFrom->_freq;
		copyTo->_data = copyFrom->_data;
		copyTo->_nodeType = copyFrom->_nodeType;

		copyTree(copyTo->_left, copyFrom->_left);
		copyTree(copyTo->_right, copyFrom->_right);
	}
}

std::string HuffmanTree::getOriginal() const
{
	return original;
}

void HuffmanTree::setOriginal(std::string input)
{
	original = input;
}
