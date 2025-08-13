extern crate huffman_coding_lib;

use huffman_coding_lib::{treeify,encode,decode};

///
/// Convert an input string into a huffman encoded bit stream, and then back into a string.
///
fn main() {
    /* enable some profiling */
    let start = std::time::Instant::now();

    /* deal with the input; this program converts string input into a poorly translated byte array */
    let input = parse(std::env::args());
    let bytes = input.as_bytes().to_vec();

    /* do the full cycle of huffman encode/decode */
    let tree = treeify(&bytes);
    let encoded = encode(&bytes, &tree);
    let decoded = decode(&encoded, &tree);

    /* translate back, again poorly */
    let translated = String::from_utf8_lossy(&decoded);

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
