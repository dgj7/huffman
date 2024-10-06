use crate::decoded_string::DecodedString;
use crate::encoded::Encoded;
use crate::tree::HuffmanTree;
use crate::input::StringInput;
use crate::input::Input;

pub mod bitvec;
pub mod debug;
pub mod decoded_byte;
pub mod decoded_string;
pub mod encoded;
pub mod input;
pub mod tree;
pub mod vec;

pub fn parse_input_string(message: &String) -> impl Input {
    return StringInput::new(&message);
}

pub fn input_to_tree(input: &impl Input) -> Option<HuffmanTree> {
    return HuffmanTree::new(input);
}

pub fn encode(input: &impl Input, tree: &Option<HuffmanTree>) -> Encoded {
    return Encoded::new(input, &tree);
}

pub fn decode(encoded: &mut Encoded, tree: Option<HuffmanTree>) -> DecodedString {
    return DecodedString::new(encoded, &tree);
}
