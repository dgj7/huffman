#include "end_to_end_tests.hpp"
#include "cut.h"
#include "huffman.hpp"

#include <string>
#include <numeric>              // std::accumulate

// todo: remove this
#include <iostream>

void scenario0(struct cut_run_t *run)
{
    /* create the input string */
    std::string input = "abbccc";

    /* create and verify the tree */
    const huffman::Tree * tree = huffman::builder::build(input);
    assert_equals(5, tree->size(), run);

    /* encode and verify */
    std::vector<bool> encoded = huffman::encoder::encode(input, *tree);
    assert_equals(9, encoded.size(), run);
    std::string stringified = std::accumulate(encoded.begin(), encoded.end(), std::string(), [](const std::string & accumulator, bool value){return accumulator + (value ? "1" : "0");});
    assert_equals(9, stringified.length(), run);
    std::cout << stringified << std::endl;
    assert_true("101111000" == stringified, run);

    /* decode and verify */
    std::string decoded = huffman::decoder::decode(encoded, *tree);
    assert_equals(6, decoded.length(), run);
    assert_true("abbccc" == decoded, run);
}

void scenario1(struct cut_run_t *run)
{
    /* create the input string */
    std::string input = "this is a sample input string. its text is being used to test the huffman coding tree.";

    /* create and verify the tree */
    const huffman::Tree * tree = huffman::builder::build(input);
    assert_equals(41, tree->size(), run);

    /* encode and verify */
    std::vector<bool> encoded = huffman::encoder::encode(input, *tree);
    assert_equals(339, encoded.size(), run);
    std::string stringified = std::accumulate(encoded.begin(), encoded.end(), std::string(), [](const std::string & accumulator, bool value){return accumulator + (value ? "1" : "0");});
    assert_equals(339, stringified.length(), run);
    assert_true("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010" == stringified, run);

    /* decode and verify */
    std::string decoded = huffman::decoder::decode(encoded, *tree);
    assert_equals(86, decoded.length(), run);
    assert_true("this is a sample input string. its text is being used to test the huffman coding tree." == decoded, run);
}

void empty_string(struct cut_run_t * run)
{
    /* create the input string */
    std::string input = "";

    /* create and verify the tree */
    const huffman::Tree * tree = huffman::builder::build(input);
    assert_equals(0, tree->size(), run);

    /* encode and verify */
    std::vector<bool> encoded = huffman::encoder::encode(input, *tree);
    assert_equals(0, encoded.size(), run);
    std::string stringified = std::accumulate(encoded.begin(), encoded.end(), std::string(), [](const std::string & accumulator, bool value){return accumulator + (value ? "1" : "0");});
    assert_equals(0, stringified.length(), run);
    assert_true("" == stringified, run);

    /* decode and verify */
    std::string decoded = huffman::decoder::decode(encoded, *tree);
    assert_equals(0, decoded.length(), run);
    assert_true("" == decoded, run);
}
