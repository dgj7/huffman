use bitvec::vec::BitVec;

pub(crate) struct DecodedByte {
    pub(crate) symbol: u8,
    pub(crate) bits: BitVec,
}

impl DecodedByte {
    pub(crate) fn new(the_symbol: u8, the_bits: BitVec) -> DecodedByte {
        DecodedByte { symbol: the_symbol, bits: the_bits }
    }
}
