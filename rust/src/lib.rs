use crate::frequency::*;
use crate::tree::*;
use ::bitvec::vec::BitVec;

pub mod debug;
pub mod decoded;
pub mod frequency;
pub mod tree;
pub mod bits;
pub mod translator;

pub fn count_frequencies(message: &Vec<u8>) -> impl FrequencyProcessor {
    return DefaultFrequencyProcessor::new(&message);
}

pub fn frequencies_to_tree(input: &impl FrequencyProcessor) -> Option<HuffmanTree> {
    return HuffmanTree::new(input);
}

// todo: potentially create our own bitvec, so that we don't require an external library to use _this_ library
pub fn encode(input: &impl FrequencyProcessor, maybe_tree: &Option<HuffmanTree>) -> BitVec {
    if maybe_tree.is_none() {
        return BitVec::new();
    }

    let tree = maybe_tree.as_ref().unwrap();
    let mut the_bits = BitVec::new();

    input.to_bytes()
        .iter()
        .for_each(|c| {
            let maybe_symbol_bits = tree.encodings.get(&c).clone();
            if maybe_symbol_bits.is_some() {
                let mut symbol_bits = maybe_symbol_bits.unwrap().clone();
                the_bits.append(&mut symbol_bits);
            }
        });

    return the_bits;
}

pub fn decode(encoded: &mut BitVec, maybe_tree: Option<HuffmanTree>) -> Vec<u8> {
    let mut decoded = Vec::new();

    if maybe_tree.is_none() {
        return decoded;
    }
    let tree = maybe_tree.as_ref().unwrap();

    let mut bits = encoded.clone();

    while !bits.is_empty() {
        let db = tree.next_decoded(&bits, &tree.root, 0, BitVec::new());
        bits.drain(0..db.bits.len());
        decoded.push(db.symbol);
    }

    return decoded;
}
