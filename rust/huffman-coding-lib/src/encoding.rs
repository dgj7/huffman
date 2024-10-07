use std::fmt;
use bitvec::vec::BitVec;

use crate::input::*;
use crate::bitvec::*;
use crate::tree::*;

pub struct Encoded {
    pub bits: BitVec,
}

pub(crate) struct DecodedByte {
    pub(crate) symbol: char,
    pub(crate) bits: BitVec,
}

pub struct DecodedString {
    pub message: String,
}

impl Encoded {
    pub(crate) fn new(input: &impl Input, maybe_tree: &Option<HuffmanTree>) -> Encoded {
        if maybe_tree.is_none() {
            return Encoded { bits: BitVec::new() }
        }

        let tree = maybe_tree.as_ref().unwrap();
        let mut the_bits = BitVec::new();

        input.to_char_array()
            .for_each(|c| {
                let maybe_symbol_bits = tree.encodings.get(&c).clone();
                if maybe_symbol_bits.is_some() {
                    let mut symbol_bits = maybe_symbol_bits.unwrap().clone();
                    the_bits.append(&mut symbol_bits);
                }
            });

        Encoded { bits: the_bits }
    }
}

impl fmt::Display for Encoded {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", PrintableBitVec::new(&self.bits))
    }
}

impl DecodedByte {
    pub(crate) fn new(the_symbol: char, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
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
