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
}
