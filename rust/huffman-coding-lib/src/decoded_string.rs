use std::fmt;
use bitvec::vec::BitVec;

use crate::encoded::*;
use crate::tree::*;

pub struct DecodedString {
    pub message: String,
}

impl DecodedString {
    pub(crate) fn new(encoded: &mut Encoded, maybe_tree: &Option<HuffmanTree>) -> DecodedString {
        if maybe_tree.is_none() {
            return DecodedString { message: String::new() };
        }
        let tree = maybe_tree.as_ref().unwrap();

        let mut builder = String::new();
        let mut bits = encoded.bits.clone();

        while !bits.is_empty() {
            let db = tree.next_decoded(&bits, &tree.root, 0, BitVec::new());
            bits.drain(0..db.bits.len());
            builder.push(db.symbol);
        }

        DecodedString { message: builder }
    }
}

impl fmt::Display for DecodedString {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}
