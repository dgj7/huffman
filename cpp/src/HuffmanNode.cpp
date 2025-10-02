#include "Huffman.hpp"

HuffmanNode::HuffmanNode(  )
{
	_left = NULL;
	_right = NULL;
}

uint64_t
HuffmanNode::size() const {
	uint64_t left = 0;
	if (this->_left != NULL) {
		left = this->_left->size();
	}

	uint64_t right = 0;
	if (this->_right != NULL) {
		right = this->_right->size();
	}

	return 1 + left + right;
}
