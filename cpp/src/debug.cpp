#include "debug.hpp"

#include <iostream>         // cout
#include <string>           // string
#include <sstream>          // stringstream

/**
 * Huffman coding tree.
 */
namespace huffman {
    /**
     * Anonymous helpers.
     */
    namespace {
        std::string leaves_to_one_line(Node *node);
    }

    /**
     * Debugging functions.
     */
    namespace debug {
        void
        tree_list(
            std::list<Tree*> &trees
        ) {
            std::cout << "list has [" << trees.size() << "] elements" << std::endl;
            for (std::list<Tree*>::iterator iter = trees.begin(); iter != trees.end(); ++iter)
            {
                Tree *tree = *iter;
                if (tree == NULL)
                {
                    std::cout << "ERROR: tree pointer is null!" << std::endl;
                }
                Node *node = tree->_root;
                if (node->_left == NULL && node->_right == NULL)
                {
                    std::cout << "\t[" << node->_freq << "] <= [" << node->_data << "]" << std::endl;
                }
                else
                {
                    std::cout << "\t[" << node->_freq << " <= INTERNAL[" << leaves_to_one_line(node) << "]" << std::endl;
                }
            }
        }
    }

    /**
     * Anonymous helpers.
     */
    namespace {
        std::string
        leaves_to_one_line(
            Node *node
        ) {
            if (node->_left == NULL && node->_right == NULL)
            {
                std::stringstream ss;
                ss << node->_freq << "|" << node->_data;
                return ss.str();
            }
            else
            {
                std::string left = leaves_to_one_line(node->_left);
                std::string right = leaves_to_one_line(node->_right);
                return left + ", " + right;
            }
        }
    }
}
