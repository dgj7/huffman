use std::fmt;
use crate::input::Input;
use crate::tree::HuffmanTree;

pub struct Encoded {
    //
}

impl Encoded {
    pub fn new(input: &dyn Input, tree: &HuffmanTree) -> Encoded {
        Encoded{}
    }
}

impl fmt::Display for Encoded {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // todo
        write!(f, "")
    }
}
