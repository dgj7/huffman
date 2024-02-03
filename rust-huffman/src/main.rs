mod input;
mod node;
mod tree;
mod encoded;
mod decoded;

fn main() {
    let input = input::StringInput::new(std::env::args());
    let tree = tree::HuffmanTree::new(&input);
    let encoded = encoded::Encoded::new(&input, &tree);
    let decoded = decoded::Decoded::new(&encoded, &tree);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded);
    println!("decoded: [{}]", decoded);
}
