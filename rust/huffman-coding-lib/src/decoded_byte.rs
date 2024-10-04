use bitvec::vec::BitVec;

pub struct DecodedByte {
    pub symbol: char,
    pub bits: BitVec,
}

impl DecodedByte {
    pub fn new(the_symbol: char, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
}
