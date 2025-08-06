use std::fmt::{Display, Formatter};
use bitvec::macros::internal::funty::Fundamental;

pub struct Bits {
    storage: Vec<u8>,
    #[allow(dead_code)]// todo
    bit_capacity: u64,
    bit_length: u64,
}

pub struct BitsIterator<'a> {
    bits: &'a Bits,
    bit_index: u64,
}

impl Bits {
    #[allow(dead_code)]// todo
    pub fn new() -> Self {
        Self {
            storage: Vec::new(),
            bit_capacity: 0,
            bit_length: 0,
        }
    }

    #[allow(dead_code)]// todo
    pub fn push(&mut self, bit: bool) {
        /* initialize storage, if needed */
        if self.bit_capacity <= self.bit_length {
            self.storage.push(0);
            self.bit_capacity += 8;
        }

        /* determine bit and byte indices within the storage, based on the current length */
        let bit_index: usize = (self.bit_length % 8) as usize;
        let byte_index: usize = (self.bit_length / 8) as usize;

        /* increment length for the next call */
        self.bit_length += 1;

        /* retrieve the byte to modify */
        let byte = &mut self.storage[byte_index];

        /* write the bit to the byte */
        write_to_byte(byte, bit_index as u8, bit);
    }

    pub fn bits_iter(&self) -> BitsIterator {
        BitsIterator {
            bits: self,
            bit_index: 0,
        }
    }
}

fn write_to_byte(byte: &mut u8, bit_index: u8, bit: bool) {
    if bit_index >= 8 {
        panic!("Index out of bounds");
    }

    let mask : u8 = !(1 << bit_index);
    let flag : u8 = (bit as u8) << bit_index;

    *byte &= mask;
    *byte |= flag;
}

fn read_from_byte(byte: u8, index: u8) -> bool {
    if index >= 8 {
        panic!("Index out of bounds");
    }

    return byte >> index & 1 == 1;
}

impl<'a> Iterator for BitsIterator<'a> {
    type Item = bool;

    fn next(&mut self) -> Option<Self::Item> {
        if self.bit_index < self.bits.bit_length {
            let bit_index = self.bit_index % 8;
            let byte_index = self.bit_index / 8;

            self.bit_index += 1;

            let byte = self.bits.storage[byte_index as usize];
            let result = read_from_byte(byte, bit_index as u8);

            return Some(result);
        } else {
            None
        }
    }
}

impl Display for Bits {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.bits_iter().for_each(|bit| {
            value.push_str(bit.as_u8().to_string().as_str());
        });
        write!(f, "{}", value)
    }
}

#[cfg(test)]
mod test {
    use crate::bits::Bits;

    #[test]
    fn test_alternate_true_first() {
        let mut bits = Bits::new();

        bits.push(true);
        bits.push(false);
        bits.push(true);
        bits.push(false);

        assert_eq!("1010", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
    }

    #[test]
    fn test_alternate_false_first() {
        let mut bits = Bits::new();

        bits.push(false);//0
        bits.push(true);//1
        bits.push(false);
        bits.push(true);

        assert_eq!("0101", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
    }

    #[test]
    fn test_only_true() {
        let mut bits = Bits::new();

        bits.push(true);
        bits.push(true);
        bits.push(true);
        bits.push(true);

        assert_eq!("1111", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
    }

    #[test]
    fn test_only_false() {
        let mut bits = Bits::new();

        bits.push(false);
        bits.push(false);
        bits.push(false);
        bits.push(false);

        assert_eq!("0000", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
    }

    #[test]
    fn test_carry_over_true() {
        let mut bits = Bits::new();

        for _ in 0..35 {
            bits.push(true);
        }// 4 bytes, +3 bits

        assert_eq!("11111111111111111111111111111111111", bits.to_string());
        assert_eq!(35, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);

        let mut bytes = String::new();
        bits.storage.into_iter().map(|b| format!("{:08b}", b)).for_each(|s| bytes.push_str(&s));
        assert_eq!("1111111111111111111111111111111100000111", bytes);
        assert_eq!(40, bytes.len());
    }

    #[test]
    fn test_carry_over_false() {
        let mut bits = Bits::new();

        for _ in 0..35 {
            bits.push(false);
        }// 4 bytes, +3 bits

        assert_eq!("00000000000000000000000000000000000", bits.to_string());
        assert_eq!(35, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);

        let mut bytes = String::new();
        bits.storage.into_iter().map(|b| format!("{:08b}", b)).for_each(|s| bytes.push_str(&s));
        assert_eq!("0000000000000000000000000000000000000000", bytes);
        assert_eq!(40, bytes.len());
    }
}
