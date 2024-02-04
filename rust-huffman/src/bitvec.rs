use std::fmt::{Display, Formatter};
use bitvec::macros::internal::funty::Fundamental;
use bitvec::vec::BitVec;

pub struct PrintableBitVec {
    pub bits: BitVec,
}

impl PrintableBitVec {
    pub fn new(the_bits: &BitVec) -> PrintableBitVec {
        PrintableBitVec { bits: the_bits.clone() }
    }
}

impl Display for PrintableBitVec {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.bits.iter().for_each(|bit| {
            // todo: hate this; feels backward
            value.push(if bit.as_bool() {'0'} else {'1'})
        });
        write!(f, "{}", value)
    }
}
