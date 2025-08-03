mod translator;

use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::frequencies_to_tree;
use huffman_coding_lib::count_frequencies;

extern crate huffman_coding_lib;

fn main() {
    let start = std::time::Instant::now();
    let input = parse(std::env::args());

    let frequencies = count_frequencies(&input);
    let tree = frequencies_to_tree(&frequencies);
    let mut encoded = encode(&frequencies, &tree);
    let decoded = decode(&mut encoded, tree);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded);
    println!("decoded: [{}]", decoded);
    println!("done. ({}ms)", start.elapsed().as_millis());
}

fn parse(args: std::env::Args) -> String {
    let args_vec: Vec<String> = args.collect();
    if args_vec.len() == 3 && args_vec[1] == "-i" {
        return args_vec[2].to_string();
    } else {
        panic!("bad args; expected -i only")
    }
}
