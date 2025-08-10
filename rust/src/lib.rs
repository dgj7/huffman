use crate::bits::Bits;
use crate::frequency::*;
use crate::tree::*;

pub mod bits;
pub mod debug;
pub mod decoded;
pub mod frequency;
pub mod translator;
pub mod tree;

pub fn count_frequencies(message: &Vec<u8>) -> impl FrequencyProcessor {
    DefaultFrequencyProcessor::new(&message)
}

pub fn frequencies_to_tree(input: &impl FrequencyProcessor) -> Option<HuffmanTree> {
    HuffmanTree::new(input)
}

pub fn encode(input: &impl FrequencyProcessor, maybe_tree: &Option<HuffmanTree>) -> Bits {
    let mut the_bits = Bits::new();
    
    if maybe_tree.is_none() {
        return the_bits;
    }

    let tree = maybe_tree.as_ref().unwrap();

    input.to_bytes().iter().for_each(|c| {
        let maybe_symbol_bits = tree.encodings.get(&c).clone();
        if maybe_symbol_bits.is_some() {
            let mut symbol_bits = maybe_symbol_bits.unwrap().clone();
            the_bits.append(&mut symbol_bits);
        }
    });

    the_bits
}

pub fn decode(encoded: &mut Bits, maybe_tree: Option<HuffmanTree>) -> Vec<u8> {
    let mut decoded = Vec::new();

    if maybe_tree.is_none() {
        return decoded;
    }
    let tree = maybe_tree.as_ref().unwrap();

    let mut bits = encoded.clone();

    while !bits.is_empty() {
        let db = tree.next_decoded(&bits, &tree.root, 0, Bits::new());
        bits.extract(0, db.bits.len());
        decoded.push(db.symbol);
    }

    decoded
}
