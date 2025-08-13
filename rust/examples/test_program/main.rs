extern crate huffman_coding_lib;

use huffman_coding_lib::count_frequencies;
use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::frequencies_to_tree;
use huffman_coding_lib::translator::{bytes_to_string, string_to_bytes};

///
/// Convert an input string into a huffman encoded bit stream, and then back into a string.
///
fn main() {
    /* enable some profiling */
    let start = std::time::Instant::now();

    /* deal with the input; this program converts string input into a poorly translated byte array */
    let input = parse(std::env::args());
    let bytes = string_to_bytes(&input);

    /* do the full cycle of huffman encode/decode */
    let frequencies = count_frequencies(&bytes);
    let tree = frequencies_to_tree(frequencies);
    let mut encoded = encode(bytes, &tree);
    let decoded = decode(&mut encoded, tree);

    /* translate back, again poorly */
    let translated = bytes_to_string(&decoded);

    /* print the output */
    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded.to_string());
    println!("decoded: [{}]", translated);
    println!("done. ({}ms)", start.elapsed().as_millis());
}

///
/// load/read/parse input parameters.
///
fn parse(args: std::env::Args) -> String {
    let args_vec: Vec<String> = args.collect();
    if args_vec.len() == 3 && args_vec[1] == "-i" {
        args_vec[2].to_string()
    } else {
        panic!("bad args; expected -i only")
    }
}
