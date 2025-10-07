#include "Huffman.hpp"

#include <bitset>

namespace huffman {
	namespace encoder {
		namespace {
			std::vector<bool> getCode(uint8_t, HuffmanTree);
			void getCodeHelper(uint8_t, Node *, Node *, bool, bool path[], uint64_t, std::vector<bool> &);
		}

		std::vector<bool>
		encode(
			std::string input,
			HuffmanTree tree
		) {
			std::vector<bool> bits;

			for(size_t c = 0; c < input.size(); c++)
			{
				char current = input[c];
				std::vector<bool> letterCode = getCode(current, tree);
				if(letterCode.size() > 0)
				{
					for(size_t d =0; d < letterCode.size(); d++)
					{
						bits.push_back(letterCode[d]);
					}
				}
			}

			return bits;
		}

		namespace {
			std::vector<bool>
			getCode(
				uint8_t code,
				HuffmanTree tree
			) {
				bool path[65535];	// max size of wide char
				std::vector<bool> retval;

				retval.clear();
				getCodeHelper(code, tree._root, tree._root, 0, path, 0, retval);

				return retval;
			}

			void
			getCodeHelper(
				uint8_t code,
				Node *node,
				Node *root,
				bool preDirection,
				bool path[],
				uint64_t pathLen,
				std::vector<bool> &ret
			) {
				if(node == NULL)
					return;

				if(node == root)
				{
					// don't do anything, didnt come from left or right
				}
				else
				{
					if(preDirection == 0)
						path[pathLen] = 0;
					else
						path[pathLen] = 1;

					pathLen++;
				}

				// if it's a leaf node AND it's the one we're looking for, return the data
				if(node->_left == NULL && node->_right == NULL)
				{
					if(node->_data == code)
					{
						for(uint64_t c = 0; c < pathLen; c++)
						{
							ret.push_back( path[c] );
						}
					}
				}
				else
				{
					getCodeHelper(code, node->_left, root, 0, path, pathLen, ret);
					getCodeHelper(code, node->_right, root, 1, path, pathLen, ret);
				}
			}
		}
	}
}
