use crate::frequency::Input;

pub struct HuffmanTree {
    //pub root: TreeNode,
}

pub struct SymbolNode {
    pub symbol: char,
    pub frequency: usize,
}

pub enum TreeNode {
    SymbolNode(SymbolNode),
    FrequencyNode(usize, SymbolNode, SymbolNode),
}

impl HuffmanTree {
    pub fn new(input: &dyn Input) -> HuffmanTree {
        let frequencies = input.to_vector();
        HuffmanTree{}
    }
}
