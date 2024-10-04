use huffman_coding_lib::HuffmanTree;
use huffman_coding_lib::StringInput;

extern crate huffman_coding_lib;

fn main() {
    let start = std::time::Instant::now();
    let input = parse(std::env::args());
    let message = StringInput::new(&input);
    let _tree = HuffmanTree::new(&message);

    println!("input:   [{}]", input);
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
