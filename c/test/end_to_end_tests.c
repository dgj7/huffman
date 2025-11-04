#include "cut.h"
#include "end_to_end_tests.h"

#include <stddef.h>
#include <string.h>             // strcmp(), strlen()

#include "frequency.h"
#include "huffman.h"
#include "tree.h"
#include "encoding.h"           // count_encodings()
#include "debug.h"              // printable_encoded_message()

void empty_string(struct cut_run_t * run)
{
    const char * input = "";
    const int length = strlen(input);
    const struct node_t * tree = create_tree(input, length);

    assert_true(0 == tree_size(tree), run);
    assert_true(0 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(0 == count_encodings(encodings), run);

    const struct encoded_message_t * const encoded = encode(input, encodings);
    assert_true(0 == strcmp("", printable_encoded_message(encoded)), run);

    const char * const decoded = decode(encoded, tree, length);
    assert_true(0 == strcmp("", decoded), run);
}

void single_byte(struct cut_run_t * run)
{
    const char * input = "f";
    const int length = strlen(input);
    const struct node_t * tree = create_tree(input, length);

    assert_true(1 == tree_size(tree), run);
    assert_true(1 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(1 == count_encodings(encodings), run);

    const struct encoded_message_t * const encoded = encode(input, encodings);
    assert_true(0 == strcmp("0", printable_encoded_message(encoded)), run);

    //const char * const decoded = decode(encoded, tree, length);
    //assert_true(0 == strcmp("f", decoded), run);
}

void short_string(struct cut_run_t * run)
{
    const char * input = "abcaba";
    const int length = strlen(input);
    const struct node_t * tree = create_tree(input, length);

    assert_true(5 == tree_size(tree), run);
    assert_true(3 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(3 == count_encodings(encodings), run);
    debug_print_encodings(encodings);

    const struct encoded_message_t * const encoded = encode(input, encodings);
    assert_true(0 == strcmp("011100110", printable_encoded_message(encoded)), run);

    //const char * const decoded = decode(encoded, tree, length);
    //assert_true(0 == strcmp("abcaba", decoded), run);
}

void main_case(struct cut_run_t * run)
{
    const char * input = "this is a sample input string. its text is being used to test the huffman coding tree.";
    const int length = strlen(input);
    const struct node_t * tree = create_tree(input, length);

    assert_true(41 == tree_size(tree), run);
    assert_true(21 == leaf_count(tree), run);

    const struct encoding_list_t * const encodings = extract_encodings(tree);
    assert_true(21 == count_encodings(encodings), run);

    const struct encoded_message_t * const encoded = encode(input, encodings);
    assert_true(0 == strcmp("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010", printable_encoded_message(encoded)), run);

    //const char * const decoded = decode(encoded, tree, length);
    //assert_true(0 == strcmp("this is a sample input string. its text is being used to test the huffman coding tree.", decoded), run);
}
