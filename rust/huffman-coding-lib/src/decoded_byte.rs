use crate::DecodedByte;
use bitvec::vec::BitVec;

impl DecodedByte {
    pub fn new(the_symbol: char, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
}
