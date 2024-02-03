mod tree;
mod frequency;
mod encoded;
mod decoded;
mod node;

fn main() {
    let input = frequency::StringInput::new(std::env::args());
    let tree = tree::HuffmanTree::new(&input);
    let encoded = encoded::Encoded::new(&input, &tree);
    let decoded = decoded::Decoded::new(&encoded, &tree);

    println!("input:   {}", input);
    println!("encoded: {}", encoded);
    println!("decoded: {}", decoded);
}
