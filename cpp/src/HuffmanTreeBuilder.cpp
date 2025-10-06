#include "Huffman.hpp"

#include <iostream>
#include <sstream>

HuffmanTreeBuilder::HuffmanTreeBuilder()
{
	//
}

HuffmanTreeBuilder::~HuffmanTreeBuilder()
{
	//
}

HuffmanTree
HuffmanTreeBuilder::build(
    std::string input
) {
	std::map<uint8_t,uint64_t> frequencies;
    for(size_t c = 0; c < input.size(); c++)
    {
        if( frequencies.find(input[c]) == frequencies.end())
        {   // if it's not in the list, add it
            frequencies[input[c]] = 1;
        }
        else
        {
            frequencies[input[c]] += 1;
        }
    }

    HuffmanTree tree = build(frequencies);
	tree.setOriginal(input);
	return tree;
}

HuffmanTree
HuffmanTreeBuilder::build(
    std::map<uint8_t,uint64_t> frequencies
) {
	std::list<HuffmanTree> treeList;
    std::map<uint8_t,uint64_t>::iterator it = frequencies.begin(  );


    while(it != frequencies.end())
    {
        HuffmanTree tempTree( it->first, it->second );
        treeList.push_back( tempTree );
        it++;
    }

    return build(treeList);
}

HuffmanTree
HuffmanTreeBuilder::build(
    std::list<HuffmanTree> trees
) {
	sort_list(trees);
    HuffmanTree tr;

    while(trees.size() > 1)
    {
        std::list<HuffmanTree>::iterator firstIter = trees.begin();
        std::list<HuffmanTree>::iterator secondIter = trees.begin();
        secondIter++;

        HuffmanTree newTree((*firstIter),(*secondIter));

        trees.erase(firstIter);
        trees.erase(secondIter);

        trees.push_back(newTree);
        sort_list(trees);

        if(trees.size() == 1)
        {
            std::list<HuffmanTree>::iterator thirdIter = trees.begin();
            tr = HuffmanTree(*thirdIter);
        }
    }

    return tr;
}

void
HuffmanTreeBuilder::sort_list(
    std::list<HuffmanTree> &trees
) {
    trees.sort();
    //debug_print(trees);
}

void
HuffmanTreeBuilder::debug_print(
    std::list<HuffmanTree> &trees
) const {
    std::cout << "----------" << std::endl;
    for (std::list<HuffmanTree>::iterator it=trees.begin(); it != trees.end(); ++it) {
        HuffmanTree element = *it;
        if (element._root->_left == NULL && element._root->_right == NULL) {
            std::cout << "[" << element.getFrequency() << "] <= [" << char(element._root->_data) << "]" << std::endl;
        } else if (element._root->_left == NULL || element._root->_right == NULL) {
            std::cout << "INVALID!!" << std::endl;
        } else {
            std::cout << "[" << element.getFrequency() << "] <= INTERNAL[" << debug_find_all_frequency_pairs(element._root) << "]" << std::endl;
        }
    }
    std::cout << "----------" << std::endl;
}

std::string
HuffmanTreeBuilder::debug_find_all_frequency_pairs(
    HuffmanNode *node
) const {
    if (node->_left != NULL && node->_right != NULL) {
        std::ostringstream ss;
        ss << debug_find_all_frequency_pairs(node->_left) << ", " << debug_find_all_frequency_pairs(node->_right);
        return ss.str();
    } else {
        std::ostringstream ss;
        ss << node->_freq << "|" << char(node->_data);
        return ss.str();
    }
}
