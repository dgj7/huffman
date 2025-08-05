use bitvec::vec::BitVec;

use crate::frequency::*;
use crate::tree::*;

pub(crate) struct DecodedByte {
    symbol: u8,
    bits: BitVec,
}

pub(crate) fn do_encode(input: &impl FrequencyProcessor, maybe_tree: &Option<HuffmanTree>) -> BitVec {
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

impl DecodedByte {
    pub(crate) fn new(the_symbol: u8, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
}

pub(crate) fn do_decode(encoded: &mut BitVec, maybe_tree: &Option<HuffmanTree>) -> Vec<u8> {
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
