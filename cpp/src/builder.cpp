#include "huffman.hpp"

#include <iostream>
#include <sstream>

/**
 * Huffman coding tree.
 */
namespace huffman {
    /**
     * Builder utility.
     */
    namespace builder {
        /**
         * Anonymous helpers.
         */
        namespace {
            bool compare(const Tree *left, const Tree *right);
        }

        /**
         * Builder method, from input string.
         */
        const Tree *
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

            return build(frequencies);
        }

        /**
         * Builder method, from input frequencies map.
         */
        const Tree *
        build(
            std::map<uint8_t,uint64_t> frequencies
        ) {
            std::list<Tree*> treeList;
            std::map<uint8_t,uint64_t>::iterator it = frequencies.begin(  );


            while(it != frequencies.end())
            {
                Tree * tempTree = new Tree( it->first, it->second );
                treeList.push_back( tempTree );
                it++;
            }

            return build(treeList);
        }

        /**
         * Builder method, from input tree list.
         */
        const Tree *
        build(
            std::list<Tree*> & trees
        ) {
            trees.sort(compare);

            while(trees.size() > 1)
            {
                std::list<Tree*>::iterator firstIter = trees.begin();
                std::list<Tree*>::iterator secondIter = trees.begin();
                secondIter++;

                Tree * first = *firstIter;
                Tree * second = *secondIter;

                Tree * newTree = new Tree(*first,*second);

                trees.erase(firstIter);
                trees.erase(secondIter);

                trees.push_back(newTree);
                trees.sort(compare);
            }

            std::list<Tree*>::iterator thirdIter = trees.begin();
            return new Tree(*(*thirdIter));
        }

        /**
         * Anonymous helpers.
         */
        namespace {
            /**
             * Compare two tree pointers, via operator <.
             */
            bool compare(const Tree *left, const Tree *right)
            {
                return (*left) < (*right);
            }
        }
    }
}
