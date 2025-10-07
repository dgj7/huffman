#include "Huffman.hpp"

#include <iostream>
#include <sstream>

namespace huffman {
    namespace builder {
        Tree
        build(
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

            Tree tree = build(frequencies);
            return tree;
        }

        Tree
        build(
            std::map<uint8_t,uint64_t> frequencies
        ) {
            std::list<Tree> treeList;
            std::map<uint8_t,uint64_t>::iterator it = frequencies.begin(  );


            while(it != frequencies.end())
            {
                Tree tempTree( it->first, it->second );
                treeList.push_back( tempTree );
                it++;
            }

            return build(treeList);
        }

        Tree
        build(
            std::list<Tree> trees
        ) {
            trees.sort();
            Tree tr;

            while(trees.size() > 1)
            {
                std::list<Tree>::iterator firstIter = trees.begin();
                std::list<Tree>::iterator secondIter = trees.begin();
                secondIter++;

                Tree newTree((*firstIter),(*secondIter));

                trees.erase(firstIter);
                trees.erase(secondIter);

                trees.push_back(newTree);
                trees.sort();

                if(trees.size() == 1)
                {
                    std::list<Tree>::iterator thirdIter = trees.begin();
                    tr = Tree(*thirdIter);
                }
            }

            return tr;
        }
    }
}
