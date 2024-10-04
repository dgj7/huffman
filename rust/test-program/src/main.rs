use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::input_to_tree;
use huffman_coding_lib::parse_input_string;

extern crate huffman_coding_lib;

fn main() {
    let start = std::time::Instant::now();
    let message = parse(std::env::args());

    let input = parse_input_string(&message);
    let tree = input_to_tree(&input);
    let mut encoded = encode(&input, &tree);
    let decoded = decode(&mut encoded, tree);

    println!("input:   [{}]", message);
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
