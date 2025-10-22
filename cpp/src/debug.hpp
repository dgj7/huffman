#ifndef DEBUG__DG__H__
#define DEBUG__DG__H__

#include "huffman.hpp"

/**
 * Huffman coding tree.
 */
namespace huffman {
    /**
     * Debugging functions.
     */
    namespace debug {
        void tree_list(std::list<Tree*> &trees);
    }
}

#endif
