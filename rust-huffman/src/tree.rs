use crate::input::Input;
use crate::node::TreeNode;

pub struct HuffmanTree {
    pub root: TreeNode,
}

impl HuffmanTree {
    pub fn new(input: &dyn Input) -> Box<HuffmanTree> {
        let mut frequencies = input.to_vector();
        if frequencies.len() == 0 {
            panic!("empty input")
        }

        while frequencies.len() > 1 {
            frequencies.sort_by(|left, right| left.frequency.partial_cmp(&right.frequency).unwrap());
            let two: Vec<TreeNode> = frequencies.drain(0..2).collect();
            let left: TreeNode = two[0].clone();
            let right: TreeNode = two[1].clone();
            let sum = left.frequency + right.frequency;
            let internal = TreeNode::new_internal(sum, left, right);
            frequencies.push(internal);
        }
        let the_root = frequencies[0].clone();

        Box::new(HuffmanTree{ root: the_root })
    }
}
