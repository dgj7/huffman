
use ::bitvec::prelude::BitVec;
use std::collections::HashMap;
use core::str::Chars;

mod input;
mod node;
mod tree;
mod decoded_byte;
mod decoded_string;
mod bitvec;
mod vec;
mod encoded;

pub trait Input {
    fn to_vector(&self) -> Vec<TreeNode>;
    fn to_char_array(&self) -> Chars;
}

pub struct StringInput {
    pub message: String,
}

#[derive(Clone)]
pub struct TreeNode {
    pub symbol: Option<char>,
    pub frequency: usize,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

pub struct HuffmanTree {
    pub root: TreeNode,
    pub encodings: HashMap<char, BitVec>,
}

pub struct Encoded {
    pub bits: BitVec,
}

pub struct DecodedByte {
    pub symbol: char,
    pub bits: BitVec,
}

pub struct DecodedString {
    pub message: String,
}

pub struct PrintableBitVec {
    pub bits: BitVec,
}




