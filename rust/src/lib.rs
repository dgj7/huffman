use crate::bits::Bits;
use crate::tree::*;
use std::collections::HashMap;

pub mod bits;
pub mod debug;
pub mod tree;

///
/// Count the frequency of each byte in the input [Vec] of [u8], returning
/// a [Vec] of [TreeNode]s.
///
/// Note that a [Vec] of [TreeNode]s is not a [HuffmanTree].
///
pub fn count_frequencies(message: &Vec<u8>) -> Vec<TreeNode> {
    let mut map: HashMap<u8, usize> = HashMap::new();
    let mut vec = vec![];

    message.iter().for_each(|symbol| {
        let value = if map.contains_key(&symbol) {
            let temp: &usize = &map.get(&symbol).unwrap().to_owned();
            temp + 1
        } else {
            1
        };

        map.insert(*symbol, value);
    });

    map.iter()
        .for_each(|elem| vec.push(TreeNode::new_leaf(*elem.0, *elem.1)));

    vec
}

///
/// Attempt to transform a [Vec] of [TreeNode]s into a [HuffmanTree].
///
pub fn frequencies_to_tree(input: Vec<TreeNode>) -> HuffmanTree {
    HuffmanTree::new(input)
}

///
/// Encode the initial [Vec] of [u8] into [Bits] with the given [HuffmanTree].
///
pub fn encode(bytes: Vec<u8>, tree: &HuffmanTree) -> Bits {
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
pub fn decode(encoded: &mut Bits, tree: HuffmanTree) -> Vec<u8> {
    let mut decoded = Vec::new();

    let mut bits = encoded.clone();

    while !bits.is_empty() {
        let db = tree.next_decoded(&bits, &tree.root, 0, Bits::new());
        bits.extract(0, db.1.len());
        decoded.push(db.0);
    }

    decoded
}
