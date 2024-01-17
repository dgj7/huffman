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

HuffmanTree HuffmanTreeBuilder::buildStandardFrequencyTree()
{
	std::map<uint8_t, uint64_t> frequencies;

    frequencies['a'] = 11602;
    frequencies['b'] = 4702;
    frequencies['c'] = 3511;
    frequencies['d'] = 2670;
    frequencies['e'] = 2007;
    frequencies['f'] = 3779;
    frequencies['g'] = 1950;
    frequencies['h'] = 7232;
    frequencies['i'] = 6286;
    frequencies['j'] = 597;
    frequencies['k'] = 590;
    frequencies['l'] = 2705;
    frequencies['m'] = 4374;
    frequencies['n'] = 2365;
    frequencies['o'] = 6264;
    frequencies['p'] = 2545;
    frequencies['q'] = 173;
    frequencies['r'] = 1653;
    frequencies['s'] = 7755;
    frequencies['t'] = 16671;
    frequencies['u'] = 1487;
    frequencies['v'] = 649;
    frequencies['w'] = 6753;
    frequencies['x'] = 37;
    frequencies['y'] = 1620;
    frequencies['z'] = 34;
	
	HuffmanTree tree = build(frequencies);
	return tree;
}
