#include "debug.hpp"

#include <iostream>         // cout
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
                std::cout << node_details(node, 1) << std::endl;
            }
        }

        void
        sort_iteration(
            std::string step
            ,bool result
            ,const Tree &left
            ,const Tree  &right
        ) {
            std::cout << "\t" << step << ": " << (result ? "true" : "false") << std::endl
                << node_details(left._root, 2) << std::endl
                << node_details(right._root, 2) << std::endl
                ;
        }

        std::string
        node_details(
            Node *node
            ,int tab_count
        ){
            std::stringstream ss;

            for (int c = 0; c < tab_count; c++)
            {
                ss << "\t";
            }

            if (node->_nodeType == leaf)
            {
                ss << "[" << node->_freq << "]->[" << node->_data << "]";
            }
            else
            {
                ss << "[" << node->_freq << "]->[" << leaves_to_one_line(node) << "]";
            }

            return ss.str();
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
            if (node->_nodeType == leaf)
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
