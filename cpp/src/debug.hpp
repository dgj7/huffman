#ifndef DEBUG__DG__H__
#define DEBUG__DG__H__

#include "huffman.hpp"

#include <string>           // std::string

/**
 * Huffman coding tree.
 */
namespace huffman {
    /**
     * Debugging functions.
     */
    namespace debug {
        /* building the main tree */
        void tree_list(std::list<Tree*> &trees);

        /* sorting the list of trees */
        void sort_iteration(std::string step, bool result, const Tree &left, const Tree &right);
        std::string node_details(Node *node, int tab_count);
    }
}

#endif
