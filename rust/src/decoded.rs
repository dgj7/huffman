use crate::bits::Bits;

pub(crate) struct DecodedByte {
    pub(crate) symbol: u8,
    pub(crate) bits: Bits,
}

impl DecodedByte {
    pub(crate) fn new(the_symbol: u8, the_bits: Bits) -> DecodedByte {
        DecodedByte {
            symbol: the_symbol,
            bits: the_bits,
        }
    }
}
