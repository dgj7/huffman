use std::ops::Deref;
use crate::TreeNode;
use crate::LEFT;
use crate::RIGHT;
use crate::HashMap;
use bitvec::prelude::BitVec;

impl TreeNode {
    pub fn new_internal(the_frequency: usize, the_left: TreeNode, the_right: TreeNode) -> TreeNode {
        TreeNode { symbol: None, frequency: the_frequency, left: Some(Box::new(the_left)), right: Some(Box::new(the_right)) }
    }

    pub fn new_leaf(the_symbol: char, the_frequency: usize) -> TreeNode {
        TreeNode { symbol: Some(the_symbol), frequency: the_frequency, left: None, right: None }
    }

    pub fn size(&self) -> usize {
        let left_size = match &self.left {
            None => 0,
            Some(x) => x.size()
        };
        let right_size = match &self.right {
            None => 0,
            Some(x) => x.size()
        };
        return 1 + left_size + right_size;
    }

    pub fn find_node(&self, direction: bool) -> &Option<Box<TreeNode>> {
        return if direction == LEFT && self.left.is_some() {
            &self.left
        } else if direction == RIGHT && self.right.is_some() {
            &self.right
        } else {
            &None
        }
    }
}

pub fn descend_tree(node: &TreeNode, map: &mut HashMap<char, BitVec>) {
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
