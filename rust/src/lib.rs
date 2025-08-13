use crate::bits::Bits;
use crate::tree::*;
use std::collections::HashMap;

pub mod bits;
pub mod debug;
pub mod translator;
pub mod tree;

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

pub fn frequencies_to_tree(input: Vec<TreeNode>) -> Option<HuffmanTree> {
    HuffmanTree::new(input)
}

pub fn encode(bytes: Vec<u8>, maybe_tree: &Option<HuffmanTree>) -> Bits {
    let mut the_bits = Bits::new();

    if maybe_tree.is_none() {
        return the_bits;
    }

    let tree = maybe_tree.as_ref().unwrap();

    bytes.iter().for_each(|c| {
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
        // todo: this should panic
        return decoded;
    }
    let tree = maybe_tree.as_ref().unwrap();

    let mut bits = encoded.clone();

    while !bits.is_empty() {
        let db = tree.next_decoded(&bits, &tree.root, 0, Bits::new());
        bits.extract(0, db.1.len());
        decoded.push(db.0);
    }

    decoded
}
