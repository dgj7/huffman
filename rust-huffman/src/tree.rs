use std::cmp::Ordering;
use std::collections::HashMap;
use std::ops::Deref;
use bit_vec::BitVec;
use crate::debug::{debug_print, debug_print_encodings};
use crate::input::Input;
use crate::node::TreeNode;

const LEFT: bool = false;
const RIGHT: bool = true;

pub struct HuffmanTree {
    pub root: TreeNode,
    pub encodings: HashMap<char, BitVec>,
}

impl HuffmanTree {
    pub fn new(input: &dyn Input) -> Box<HuffmanTree> {
        /* get a vector with all the frequencies, represented as leaf nodes */
        let mut frequencies = input.to_vector();
        //debug_print(&mut frequencies);

        /* presently failing for an empty frequency list */
        if frequencies.len() == 0 {
            // todo: implement an empty tree
            panic!("empty input")
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
            //debug_print(&mut frequencies);
        }
        let the_root = frequencies[0].clone();

        /* descend the tree to gather all codes */
        let mut the_encodings: HashMap<char, BitVec> = HashMap::new();
        descend_tree(&the_root, &mut the_encodings);
        debug_print_encodings(&the_encodings);

        /* return the new tree */
        Box::new(HuffmanTree { root: the_root, encodings: the_encodings })
    }
}

fn descend_tree(node: &TreeNode, map: &mut HashMap<char, BitVec>) {
    if node.left.is_some() {
        descend(node.left.as_ref().unwrap().deref(), map, BitVec::new(), LEFT);
    }

    if node.right.is_some() {
        descend(node.right.as_ref().unwrap().deref(), map, BitVec::new(), RIGHT);
    }
}

fn descend(node: &TreeNode, map: &mut HashMap<char, BitVec>, mut bits: BitVec, bit: bool) {
    /* add to the current codes */
    bits.push(bit);

    /* next step depends on whether we have left/right, or a symbol */
    if node.left.is_some() && node.right.is_some() {
        /* if left/right exist, we need to descend with new bit vectors */
        descend(node.left.as_ref().unwrap().deref(), map, bits.clone(), LEFT);
        descend(node.right.as_ref().unwrap().deref(), map, bits.clone(), RIGHT);
    } else if node.symbol.is_some() {
        /* if the symbol is here, then we're done and can add to the map */
        map.insert(node.symbol.unwrap(), bits);
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
