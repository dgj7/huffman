use bitvec::vec::BitVec;

pub(crate) struct DecodedByte {
    pub(crate) symbol: char,
    pub(crate) bits: BitVec,
}

impl DecodedByte {
    pub(crate) fn new(the_symbol: char, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
}
