use crate::bits::Bits;
use crate::frequency::count_frequencies;
use crate::tree::*;

pub mod bits;
pub mod debug;
pub mod tree;
mod frequency;

///
/// Attempt to transform a [Vec] of [u8]s into a [HuffmanTree].
///
pub fn treeify(bytes: &Vec<u8>) -> HuffmanTree {
    let frequencies = count_frequencies(&bytes);
    HuffmanTree::new(frequencies)
}

///
/// Encode the initial [Vec] of [u8] into [Bits] with the given [HuffmanTree].
///
pub fn encode(bytes: &Vec<u8>, tree: &HuffmanTree) -> Bits {
    let mut the_bits = Bits::new();

    bytes.iter().for_each(|c| {
        let maybe_symbol_bits = tree.encodings.get(&c).clone();
        if maybe_symbol_bits.is_some() {
            let mut symbol_bits = maybe_symbol_bits.unwrap().clone();
            the_bits.append(&mut symbol_bits);
        }
    });

    the_bits
}

///
/// Decode the given [Bits] into [Vec] of [u8] with the given [HuffmanTree].
///
pub fn decode(encoded: &Bits, tree: &HuffmanTree) -> Vec<u8> {
    let mut decoded = Vec::new();

    let mut bits = encoded.clone();

    while !bits.is_empty() {
        let db = tree.next_decoded(&bits, &tree.root, 0, Bits::new());
        bits.extract(0, db.1.len());
        decoded.push(db.0);
    }

    decoded
}
