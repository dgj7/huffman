use crate::tree::LEFT;
use crate::tree::RIGHT;

#[derive(Clone)]
pub struct TreeNode {
    pub symbol: Option<char>,
    pub frequency: usize,
    pub left: Option<Box<TreeNode>>,
    pub right: Option<Box<TreeNode>>,
}

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
