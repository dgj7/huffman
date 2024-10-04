use std::fmt::{Display, Formatter};
use bitvec::macros::internal::funty::Fundamental;
use bitvec::vec::BitVec;

pub(crate) struct PrintableBitVec {
    pub(crate) bits: BitVec,
}

impl PrintableBitVec {
    pub(crate) fn new(the_bits: &BitVec) -> PrintableBitVec {
        PrintableBitVec { bits: the_bits.clone() }
    }
}

impl Display for PrintableBitVec {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.bits.iter().for_each(|bit| {
            value.push_str(bit.as_u8().to_string().as_str());
        });
        write!(f, "{}", value)
    }
}
