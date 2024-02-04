use std::cmp::Ordering;
use std::collections::HashMap;
use bitvec::macros::internal::funty::Fundamental;
use bitvec::vec::BitVec;
use crate::bitvec::PrintableBitVec;
use crate::decoded_byte::DecodedByte;
use crate::input::Input;
use crate::node::{descend_tree, TreeNode};

pub const LEFT: bool = false;
pub const RIGHT: bool = true;

pub struct HuffmanTree {
    pub root: TreeNode,
    pub encodings: HashMap<char, BitVec>,
}

impl HuffmanTree {
    pub fn new(input: &dyn Input) -> Option<HuffmanTree> {
        /* get a vector with all the frequencies, represented as leaf nodes */
        let mut frequencies = input.to_vector();
        //debug_print(&mut frequencies);

        /* presently failing for an empty frequency list */
        if frequencies.len() == 0 {
            return None;
        }

        /* merge elements in the frequency list until there is only a single element; that element is the tree's root */
        while frequencies.len() > 1 {
            sort(&mut frequencies);
            let two: Vec<TreeNode> = frequencies.drain(0..2).collect();
            let left: TreeNode = two[0].clone();
            let right: TreeNode = two[1].clone();
            let sum = left.frequency + right.frequency;
            let internal = TreeNode::new_internal(sum, left, right);
            frequencies.push(internal);
            //crate::debug::debug_print(&mut frequencies);
        }
        let the_root = frequencies[0].clone();

        /* descend the tree to gather all codes */
        let mut the_encodings: HashMap<char, BitVec> = HashMap::new();
        descend_tree(&the_root, &mut the_encodings);
        //crate::debug::debug_print_encodings(&the_encodings);

        /* return the new tree */
        Some(HuffmanTree { root: the_root, encodings: the_encodings })
    }

    pub fn next_decoded(&self, encoded_bits: &BitVec, node: &TreeNode, index: usize, mut the_bits: BitVec) -> DecodedByte {
        let bit: bool = (encoded_bits.get(index).unwrap().as_u8()) != 0;// funty's as_bool() returns flipped bit
        the_bits.push(bit);
        let maybe_sub_node = node.find_node(bit);
        if maybe_sub_node.is_some() {
            let sub_node = maybe_sub_node.clone().unwrap();

            return match sub_node.symbol {
                None => self.next_decoded(encoded_bits, sub_node.as_ref(), index + 1, the_bits),
                Some(x) => DecodedByte::new(x, the_bits)
            };
        } else {
            // todo: unit test this
            panic!("[{}] is not a valid code", PrintableBitVec::new(&the_bits));
        }
    }
}

pub fn sort(vec: &mut Vec<TreeNode>) {
    vec.sort_by(|left, right| {
        let freq_result = left.frequency.partial_cmp(&right.frequency).unwrap();

        return if freq_result == Ordering::Equal {
            if left.symbol.is_some() && right.symbol.is_some() {
                left.symbol.unwrap().partial_cmp(&right.symbol.unwrap()).unwrap()
            } else {
                left.size().partial_cmp(&right.size()).unwrap()
            }
        } else {
            freq_result
        }
    });
}
