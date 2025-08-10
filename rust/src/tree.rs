use crate::bits::Bits;
use crate::decoded::*;
use crate::frequency::*;
use std::cmp::Ordering;
use std::collections::HashMap;
use std::ops::Deref;

pub(crate) const LEFT: bool = false;
pub(crate) const RIGHT: bool = true;

///
/// Internal storage for [HuffmanTree].
///
/// Represents both 'internal' and 'leaf' nodes, where
/// *  internal nodes store only frequency (of combined leaf child symbols), and
/// *  leaf nodes store a 'symbol' (byte).
///
#[derive(Clone)]
pub struct TreeNode {
    pub symbol: Option<u8>,
    pub frequency: usize,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

///
/// Huffman tree structure, owner of:
/// * root ([TreeNode]), with tree data
/// * encodings [HashMap], storing encoded data for each byte symbol
///
pub struct HuffmanTree {
    pub root: TreeNode,
    pub encodings: HashMap<u8, Bits>,
}

impl HuffmanTree {
    pub(crate) fn new(input: &impl FrequencyProcessor) -> Option<HuffmanTree> {
        /* get a vector with all the frequencies, represented as leaf nodes */
        let mut frequencies = input.to_frequencies();
        //crate::debug::debug_print(&mut frequencies);

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
        let mut the_encodings: HashMap<u8, Bits> = HashMap::new();
        descend_tree(&the_root, &mut the_encodings);
        //crate::debug::debug_print_encodings(&the_encodings);

        /* return the new tree */
        Some(HuffmanTree {
            root: the_root,
            encodings: the_encodings,
        })
    }

    pub(crate) fn next_decoded(
        &self,
        encoded_bits: &Bits,
        node: &TreeNode,
        index: usize,
        mut the_bits: Bits,
    ) -> DecodedByte {
        let bit: bool = encoded_bits.read(index);
        the_bits.push(bit);
        let maybe_sub_node = node.find_node(bit);
        if maybe_sub_node.is_some() {
            let sub_node = maybe_sub_node.clone().unwrap();

            return match sub_node.symbol {
                None => self.next_decoded(encoded_bits, sub_node.as_ref(), index + 1, the_bits),
                Some(x) => DecodedByte::new(x, the_bits),
            };
        } else {
            // todo: unit test this
            panic!("[{}] is not a valid code", &the_bits);
        }
    }
}

impl TreeNode {
    pub(crate) fn new_internal(
        the_frequency: usize,
        the_left: TreeNode,
        the_right: TreeNode,
    ) -> TreeNode {
        TreeNode {
            symbol: None,
            frequency: the_frequency,
            left: Some(Box::new(the_left)),
            right: Some(Box::new(the_right)),
        }
    }

    pub(crate) fn new_leaf(the_symbol: u8, the_frequency: usize) -> TreeNode {
        TreeNode {
            symbol: Some(the_symbol),
            frequency: the_frequency,
            left: None,
            right: None,
        }
    }

    pub(crate) fn size(&self) -> usize {
        let left_size = match &self.left {
            None => 0,
            Some(x) => x.size(),
        };
        let right_size = match &self.right {
            None => 0,
            Some(x) => x.size(),
        };
        return 1 + left_size + right_size;
    }

    pub(crate) fn find_node(&self, direction: bool) -> &Option<Box<TreeNode>> {
        return if direction == LEFT && self.left.is_some() {
            &self.left
        } else if direction == RIGHT && self.right.is_some() {
            &self.right
        } else {
            &None
        };
    }
}

pub(crate) fn descend_tree(node: &TreeNode, map: &mut HashMap<u8, Bits>) {
    if node.left.is_some() {
        descend(node.left.as_ref().unwrap().deref(), map, Bits::new(), LEFT);
    }

    if node.right.is_some() {
        descend(
            node.right.as_ref().unwrap().deref(),
            map,
            Bits::new(),
            RIGHT,
        );
    }
}

fn descend(node: &TreeNode, map: &mut HashMap<u8, Bits>, mut bits: Bits, bit: bool) {
    /* add to the current codes */
    bits.push(bit);

    /* next step depends on whether we have left/right, or a symbol */
    if node.left.is_some() && node.right.is_some() {
        /* if left/right exist, we need to descend with new bit vectors */
        descend(node.left.as_ref().unwrap().deref(), map, bits.clone(), LEFT);
        descend(
            node.right.as_ref().unwrap().deref(),
            map,
            bits.clone(),
            RIGHT,
        );
    } else if node.symbol.is_some() {
        /* if the symbol is here, then we're done and can add to the map */
        map.insert(node.symbol.unwrap(), bits);
    }
}

pub(crate) fn sort(vec: &mut Vec<TreeNode>) {
    vec.sort_by(|left, right| {
        let freq_result = left.frequency.partial_cmp(&right.frequency).unwrap();

        return if freq_result == Ordering::Equal {
            if left.symbol.is_some() && right.symbol.is_some() {
                left.symbol
                    .unwrap()
                    .partial_cmp(&right.symbol.unwrap())
                    .unwrap()
            } else {
                left.size().partial_cmp(&right.size()).unwrap()
            }
        } else {
            freq_result
        };
    });
}
