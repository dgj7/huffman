use std::env::args;

mod tree;
mod frequency;
mod encoded;
mod decoded;

fn main() {
    let input = frequency::Input::new(args());
    let tree = tree::HuffmanTree::new(&input);
    let encoded = encoded::Encoded::new(&input, &tree);
    let decoded = decoded::Decoded::new(&encoded, &tree);

    println!("input:   {}", input);
    println!("encoded: {}", encoded);
    println!("decoded: {}", decoded);
}
