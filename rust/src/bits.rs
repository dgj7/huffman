#![allow(dead_code)]// todo: remove this eventually

use std::fmt::{Display, Formatter};
use bitvec::macros::internal::funty::Fundamental;

///
/// Data structure for storage and access to an array of bits.
///
#[derive(Clone)]
pub struct Bits {
    storage: Vec<u8>,
    bit_capacity: usize,
    bit_length: usize,
}

///
/// Iterate over [Bits], one bit at a time.
///
pub struct BitsIterator<'a> {
    bits: &'a Bits,
    bit_index: usize,
}

///
/// Iterate over [Bits], one byte at a time.
///
pub struct BytesIterator<'a> {
    bits: &'a Bits,
    byte_index: usize,
    max: usize,
}

impl Bits {
    pub fn new() -> Self {
        Self {
            storage: Vec::new(),
            bit_capacity: 0,
            bit_length: 0,
        }
    }

    pub fn push(&mut self, bit: bool) {
        /* initialize storage, if needed */
        if self.bit_capacity <= self.bit_length {
            self.storage.push(0);
            self.bit_capacity += 8;
        }

        /* determine bit and byte indices within the storage, based on the current length */
        let bit_index: usize = self.bit_length % 8;
        let byte_index: usize = self.bit_length / 8;

        /* increment length for the next call */
        self.bit_length += 1;

        /* retrieve the byte to modify */
        let byte = &mut self.storage[byte_index];

        /* write the bit to the byte */
        write_to_byte(byte, bit_index, bit);
    }

    pub fn append(&mut self, other: &Bits) {
        other.iter().for_each(|bit| {
            self.push(bit);
        });
    }

    pub fn iter(&self) -> BitsIterator {
        BitsIterator {
            bits: self,
            bit_index: 0,
        }
    }

    pub fn bytes_iter(&self) -> BytesIterator {
        BytesIterator {
            bits: self,
            byte_index: 0,
            max: self.storage.len(),
        }
    }

    ///
    /// Extract (start, start+count-1) bits and return as a new [Bits].
    ///
    pub fn extract(&mut self, start: usize, count: usize) -> Bits {
        /* storage for output */
        let mut bits = Bits::new();

        /* sc if count < 1 */
        if count < 1 {
            return bits;
        }

        /* iterate over the bits specified by the range */
        for current_index in start..start + count {
            /* determine the value of the replacement bit; it either comes from later in the array, or it's 0 because there isn't a later */
            let replacement_index = start + count;
            let replacement_byte_index = replacement_index / 8;
            let replacement_bit: bool = if replacement_byte_index > self.storage.len() - 1 {
                false
            } else {
                let replacement_source_byte = self.storage[replacement_byte_index];
                let replacement_bit_index = replacement_index % 8;
                read_from_byte(replacement_source_byte, replacement_bit_index)
            };

            /* get the value of the current bit, and store it in the output */
            let current_byte_index = current_index / 8;
            let mut current_byte = self.storage[current_byte_index];
            let current_bit_index = current_index % 8;
            let current_bit = read_from_byte(current_byte, current_bit_index);
            bits.push(current_bit);

            /* overwrite the current bit index with the replacement bit */
            write_to_byte(&mut current_byte, current_bit_index, replacement_bit);
        }

        /* remove (zero) the last 'count' bits */
        for remove_index in (self.bit_capacity - count) .. self.bit_capacity {
            let remove_byte_index = remove_index / 8;
            let remove_bit_index = remove_index % 8;
            let remove_byte = &mut self.storage[remove_byte_index];
            write_to_byte(remove_byte, remove_bit_index, false);
        }

        /* update size */
        self.bit_length -= count;

        /* determine if any storage bytes can be freed */
        let needed_storage_bytes = self.bit_capacity / 8;
        let mut actual_storage_bytes = self.storage.len();
        while needed_storage_bytes < actual_storage_bytes {
            self.storage.remove(actual_storage_bytes - 1);
            actual_storage_bytes -= 1;
        }

        /* update capacity; must always be multiple of 8 */
        self.bit_capacity = if self.bit_length == 0 {
            0
        } else {
            actual_storage_bytes * 8
        };

        /* done */
        bits
    }

    ///
    /// Determine if the array is empty.
    ///
    pub fn is_empty(&self) -> bool {
        self.bit_length == 0
    }
}

fn write_to_byte(byte: &mut u8, bit_index: usize, bit: bool) {
    if bit_index >= 8 {
        panic!("Index out of bounds");
    }

    let mask : u8 = !(1 << bit_index);
    let flag : u8 = (bit as u8) << bit_index;

    *byte &= mask;
    *byte |= flag;
}

fn read_from_byte(byte: u8, index: usize) -> bool {
    if index >= 8 {
        panic!("Index out of bounds");
    }

    byte >> index & 1 == 1
}

impl<'a> Iterator for BitsIterator<'a> {
    type Item = bool;

    fn next(&mut self) -> Option<Self::Item> {
        if self.bit_index < self.bits.bit_length {
            let bit_index: usize = (self.bit_index % 8) as usize;
            let byte_index: usize = (self.bit_index / 8) as usize;

            self.bit_index += 1;

            let byte = self.bits.storage[byte_index as usize];
            let result = read_from_byte(byte, bit_index);

            Some(result)
        } else {
            None
        }
    }
}

impl<'a> Iterator for BytesIterator<'a> {
    type Item = u8;

    fn next(&mut self) -> Option<Self::Item> {
        let prior_byte_index = self.byte_index;
        self.byte_index += 1;
        if prior_byte_index < self.max {
            Some(self.bits.storage[prior_byte_index])
        } else {
            None
        }
    }
}

impl Display for Bits {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.iter().for_each(|bit| {
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

        /* test push */
        bits.push(true);
        bits.push(false);
        assert_eq!("10", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(true);
        appendage.push(false);
        bits.append(&appendage);
        assert_eq!("1010", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(5, byte1);
        assert_eq!(None, byte2);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        assert_eq!("00000101", bytes_string);
        assert_eq!(8, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("1010", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("01", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("10", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
        assert_eq!("1010", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_alternate_false_first() {
        let mut bits = Bits::new();

        /* test push */
        bits.push(false);
        bits.push(true);
        assert_eq!("01", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(false);
        appendage.push(true);
        bits.append(&appendage);
        assert_eq!("0101", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(10, byte1);
        assert_eq!(None, byte2);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        assert_eq!("00001010", bytes_string);
        assert_eq!(8, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("0101", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("10", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("01", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
        assert_eq!("0101", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_only_true() {
        let mut bits = Bits::new();

        /* test push */
        bits.push(true);
        bits.push(true);
        assert_eq!("11", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(true);
        appendage.push(true);
        bits.append(&appendage);
        assert_eq!("1111", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(15, byte1);
        assert_eq!(None, byte2);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        assert_eq!("00001111", bytes_string);
        assert_eq!(8, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("1111", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("11", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("11", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
        assert_eq!("1111", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_only_false() {
        let mut bits = Bits::new();

        /* test push */
        bits.push(false);
        bits.push(false);
        assert_eq!("00", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(false);
        appendage.push(false);
        bits.append(&appendage);
        assert_eq!("0000", bits.to_string());
        assert_eq!(4, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(0, byte1);
        assert_eq!(None, byte2);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        assert_eq!("00000000", bytes_string);
        assert_eq!(8, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("0000", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("00", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("00", bits.to_string());
        assert_eq!(2, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);
        assert_eq!("0000", clone.to_string());
        assert_eq!(4, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_carry_over_true() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0..28 {
            bits.push(true);
        }// 4 bytes, +3 bits
        assert_eq!("1111111111111111111111111111", bits.to_string());
        assert_eq!(28, bits.bit_length);
        assert_eq!(32, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 7 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("11111111111111111111111111111111111", bits.to_string());
        assert_eq!(35, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next().unwrap();
        let byte3 = byte_iterator.next().unwrap();
        let byte4 = byte_iterator.next().unwrap();
        let byte5 = byte_iterator.next().unwrap();
        let byte6 = byte_iterator.next();
        assert_eq!(255, byte1);
        assert_eq!(255, byte2);
        assert_eq!(255, byte3);
        assert_eq!(255, byte4);
        assert_eq!(7, byte5);
        assert_eq!(None, byte6);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        bytes_string.push_str(&format!("{:08b}", byte2));
        bytes_string.push_str(&format!("{:08b}", byte3));
        bytes_string.push_str(&format!("{:08b}", byte4));
        bytes_string.push_str(&format!("{:08b}", byte5));
        assert_eq!("1111111111111111111111111111111100000111", bytes_string);
        assert_eq!(40, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("11111111111111111111111111111111111", clone.to_string());
        assert_eq!(35, clone.bit_length);
        assert_eq!(40, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("11", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("111111111111111111111111111111111", bits.to_string());
        assert_eq!(33, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);
        assert_eq!("11111111111111111111111111111111111", clone.to_string());
        assert_eq!(35, clone.bit_length);
        assert_eq!(40, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_carry_over_false() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0..26 {
            bits.push(false);
        }// 4 bytes, +3 bits
        assert_eq!("00000000000000000000000000", bits.to_string());
        assert_eq!(26, bits.bit_length);
        assert_eq!(32, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 9 {
            appendage.push(false);
        }
        bits.append(&appendage);
        assert_eq!("00000000000000000000000000000000000", bits.to_string());
        assert_eq!(35, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next().unwrap();
        let byte3 = byte_iterator.next().unwrap();
        let byte4 = byte_iterator.next().unwrap();
        let byte5 = byte_iterator.next().unwrap();
        let byte6 = byte_iterator.next();
        assert_eq!(0, byte1);
        assert_eq!(0, byte2);
        assert_eq!(0, byte3);
        assert_eq!(0, byte4);
        assert_eq!(0, byte5);
        assert_eq!(None, byte6);
        let mut bytes_string = String::new();
        bytes_string.push_str(&format!("{:08b}", byte1));
        bytes_string.push_str(&format!("{:08b}", byte2));
        bytes_string.push_str(&format!("{:08b}", byte3));
        bytes_string.push_str(&format!("{:08b}", byte4));
        bytes_string.push_str(&format!("{:08b}", byte5));
        assert_eq!("0000000000000000000000000000000000000000", bytes_string);
        assert_eq!(40, bytes_string.len());

        /* test clone */
        let clone = bits.clone();
        assert_eq!("00000000000000000000000000000000000", clone.to_string());
        assert_eq!(35, clone.bit_length);
        assert_eq!(40, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("00", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("000000000000000000000000000000000", bits.to_string());
        assert_eq!(33, bits.bit_length);
        assert_eq!(40, bits.bit_capacity);
        assert_eq!("00000000000000000000000000000000000", clone.to_string());
        assert_eq!(35, clone.bit_length);
        assert_eq!(40, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_empty() {
        let mut bits = Bits::new();

        /* test push: unnecessary */
        /* test append: unnecessary */

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next();
        assert_eq!(None, byte1);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("", clone.to_string());
        assert_eq!(0, clone.bit_length);
        assert_eq!(0, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(0, 0);
        assert_eq!("", extracted.to_string());
        assert_eq!(0, extracted.bit_length);
        assert_eq!(0, extracted.bit_capacity);
        assert_eq!("", bits.to_string());
        assert_eq!(0, bits.bit_length);
        assert_eq!(0, bits.bit_capacity);
        assert_eq!("", clone.to_string());
        assert_eq!(0, clone.bit_length);
        assert_eq!(0, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(true, bits.is_empty());
        assert_eq!(true, clone.is_empty());
        assert_eq!(true, extracted.is_empty());
    }

    #[test]
    fn test_extract_to_empty() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0 .. 8 {
            bits.push(true);
        }

        /* test append: unnecessary */

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(255, byte1);
        assert_eq!(None, byte2);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(0, 8);
        assert_eq!("11111111", extracted.to_string());
        assert_eq!(8, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("", bits.to_string());
        assert_eq!(0, bits.bit_length);
        assert_eq!(0, bits.bit_capacity);
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(true, bits.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    #[should_panic]
    fn test_extract_out_of_range() {
        let mut bits = Bits::new();

        /* test extract */
        bits.extract(0, 1);
    }

    #[test]
    fn test_scenario1() {
        let mut bits = Bits::new();

        /* test push */
        bits.push(true);
        bits.push(false);
        bits.push(true);
        bits.push(false);
        bits.push(true);
        bits.push(false);
        bits.push(true);
        bits.push(false);
        bits.push(true);
        bits.push(false);
        bits.push(true);
        assert_eq!("10101010101", bits.to_string());
        assert_eq!(11, bits.bit_length);
        assert_eq!(16, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(true);
        appendage.push(false);
        appendage.push(true);
        appendage.push(false);
        appendage.push(true);
        appendage.push(false);
        appendage.push(true);
        appendage.push(false);
        appendage.push(true);
        bits.append(&appendage);
        assert_eq!("10101010101101010101", bits.to_string());
        assert_eq!(20, bits.bit_length);
        assert_eq!(24, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next().unwrap();
        let byte3 = byte_iterator.next().unwrap();
        let byte4 = byte_iterator.next();
        assert_eq!(85, byte1);
        assert_eq!(173, byte2);
        assert_eq!(10, byte3);
        assert_eq!(None, byte4);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("10101010101101010101", clone.to_string());
        assert_eq!(20, clone.bit_length);
        assert_eq!(24, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("01", extracted.to_string());
        assert_eq!(2, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("101010101011010101", bits.to_string());
        assert_eq!(18, bits.bit_length);
        assert_eq!(24, bits.bit_capacity);
        assert_eq!("10101010101101010101", clone.to_string());
        assert_eq!(20, clone.bit_length);
        assert_eq!(24, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_scenario2() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0 .. 16 {
            bits.push(true);
        }
        assert_eq!("1111111111111111", bits.to_string());
        assert_eq!(16, bits.bit_length);
        assert_eq!(16, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 3 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("1111111111111111111", bits.to_string());
        assert_eq!(19, bits.bit_length);
        assert_eq!(24, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next().unwrap();
        let byte3 = byte_iterator.next().unwrap();
        let byte4 = byte_iterator.next();
        assert_eq!(255, byte1);
        assert_eq!(255, byte2);
        assert_eq!(7, byte3);
        assert_eq!(None, byte4);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("1111111111111111111", clone.to_string());
        assert_eq!(19, clone.bit_length);
        assert_eq!(24, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(10, 3);
        assert_eq!("111", extracted.to_string());
        assert_eq!(3, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("1111111111111111", bits.to_string());
        assert_eq!(16, bits.bit_length);
        assert_eq!(24, bits.bit_capacity);
        assert_eq!("1111111111111111111", clone.to_string());
        assert_eq!(19, clone.bit_length);
        assert_eq!(24, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }

    #[test]
    fn test_scenario3() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0 .. 7 {
            bits.push(true);
        }
        assert_eq!("1111111", bits.to_string());
        assert_eq!(7, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 1 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("11111111", bits.to_string());
        assert_eq!(8, bits.bit_length);
        assert_eq!(8, bits.bit_capacity);

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(255, byte1);
        assert_eq!(None, byte2);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test extract */
        let extracted = bits.extract(0, 8);
        assert_eq!("11111111", extracted.to_string());
        assert_eq!(8, extracted.bit_length);
        assert_eq!(8, extracted.bit_capacity);
        assert_eq!("", bits.to_string());
        assert_eq!(0, bits.bit_length);
        assert_eq!(0, bits.bit_capacity);
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.bit_length);
        assert_eq!(8, clone.bit_capacity);

        /* test is_empty */
        assert_eq!(true, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }
}
