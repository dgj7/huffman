use std::fmt;
use bitvec::vec::BitVec;
use crate::bitvec::PrintableBitVec;
use crate::input::Input;
use crate::tree::HuffmanTree;

pub struct Encoded {
    pub bits: BitVec,
}

impl Encoded {
    pub fn new(input: &dyn Input, tree: &HuffmanTree) -> Encoded {
        let mut the_bits = BitVec::new();

        input.to_char_array()
            .for_each(|c| {
                let maybe_symbol_bits = tree.encodings.get(&c).clone();
                if maybe_symbol_bits.is_some() {
                    let mut symbol_bits = maybe_symbol_bits.unwrap().clone();
                    the_bits.append(&mut symbol_bits);
                }
            });

        Encoded { bits: the_bits }
    }
}

impl fmt::Display for Encoded {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", PrintableBitVec::new(&self.bits))
    }
}
