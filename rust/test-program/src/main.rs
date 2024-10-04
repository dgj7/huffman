use huffman_coding_lib::DecodedString;
use huffman_coding_lib::Encoded;
use huffman_coding_lib::HuffmanTree;
use huffman_coding_lib::StringInput;

extern crate huffman_coding_lib;

fn main() {
    let start = std::time::Instant::now();
    let message = parse(std::env::args());
    let input = StringInput::new(&message);
    let tree = HuffmanTree::new(&input);
    let mut encoded = Encoded::new(&input, &tree);
    let decoded = DecodedString::new(&mut encoded, &tree);

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
