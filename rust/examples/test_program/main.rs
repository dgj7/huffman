extern crate huffman_coding_lib;

use huffman_coding_lib::count_frequencies;
use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::frequencies_to_tree;
use huffman_coding_lib::translator::{bytes_to_string, string_to_bytes};

fn main() {
    let start = std::time::Instant::now();
    let input = parse(std::env::args());

    let bytes = string_to_bytes(&input);
    let frequencies = count_frequencies(&bytes);
    let tree = frequencies_to_tree(&frequencies);
    let mut encoded = encode(&frequencies, &tree);
    let decoded = decode(&mut encoded, tree);
    let translated = bytes_to_string(&decoded);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded.to_string());
    println!("decoded: [{}]", translated);
    println!("done. ({}ms)", start.elapsed().as_millis());
}

fn parse(args: std::env::Args) -> String {
    let args_vec: Vec<String> = args.collect();
    if args_vec.len() == 3 && args_vec[1] == "-i" {
        args_vec[2].to_string()
    } else {
        panic!("bad args; expected -i only")
    }
}
