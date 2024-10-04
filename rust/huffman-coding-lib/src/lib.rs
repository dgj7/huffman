use crate::decoded_string::DecodedString;
use crate::encoded::Encoded;
use crate::tree::HuffmanTree;
use crate::input::StringInput;
use crate::input::Input;

pub mod input;
pub mod node;
pub mod tree;
pub mod decoded_byte;
pub mod decoded_string;
pub mod bitvec;
pub mod vec;
pub mod encoded;
pub mod debug;

pub fn parse_message(message: &String) -> impl Input {
    return StringInput::new(&message);
}

pub fn to_tree(input: &impl Input) -> Option<HuffmanTree> {
    return HuffmanTree::new(input);
}

pub fn encode(input: &impl Input, tree: &Option<HuffmanTree>) -> Encoded {
    return Encoded::new(input, &tree);
}

pub fn decode(encoded: &mut Encoded, tree: Option<HuffmanTree>) -> DecodedString {
    return DecodedString::new(encoded, &tree);
}
