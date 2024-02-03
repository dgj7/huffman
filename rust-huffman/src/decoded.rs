use std::fmt;
use crate::encoded::Encoded;
use crate::tree::HuffmanTree;

pub struct Decoded {
    //
}

impl Decoded {
    pub fn new(encoded: &Encoded, tree: &HuffmanTree) -> Decoded {
        Decoded{}
    }
}

impl fmt::Display for Decoded {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // todo
        write!(f, "")
    }
}
