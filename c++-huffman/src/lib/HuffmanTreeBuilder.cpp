#include "Huffman.hpp"

HuffmanTreeBuilder::HuffmanTreeBuilder()
{
	//
}

HuffmanTreeBuilder::~HuffmanTreeBuilder()
{
	//
}

HuffmanTree HuffmanTreeBuilder::build(std::string input)
{
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

HuffmanTree HuffmanTreeBuilder::build(std::map<uint8_t,uint64_t> frequencies)
{
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

HuffmanTree HuffmanTreeBuilder::build(std::list<HuffmanTree> trees)
{
	trees.sort();
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
        trees.sort();

        if(trees.size() == 1)
        {
            std::list<HuffmanTree>::iterator thirdIter = trees.begin();
            tr = HuffmanTree(*thirdIter);
        }
    }

    return tr;
}
