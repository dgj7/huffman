#[cfg(test)]
mod test {
    use huffman_coding_lib::bits::Bits;

    #[test]
    fn test_alternate_true_first() {
        let mut bits = Bits::new();

        /* test push */
        bits.push(true);
        bits.push(false);
        assert_eq!("10", bits.to_string());
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(true);
        appendage.push(false);
        bits.append(&appendage);
        assert_eq!("1010", bits.to_string());
        assert_eq!(4, bits.len());
        assert_eq!(8, bits.capacity());

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
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

        /* test extract */
        let extracted = bits.extract(0, 1);
        assert_eq!("1", extracted.to_string());
        assert_eq!(1, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("010", bits.to_string());
        assert_eq!(3, bits.len());
        assert_eq!(8, bits.capacity());
        assert_eq!("1010", clone.to_string());
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

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
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(false);
        appendage.push(true);
        bits.append(&appendage);
        assert_eq!("0101", bits.to_string());
        assert_eq!(4, bits.len());
        assert_eq!(8, bits.capacity());

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
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("10", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("01", bits.to_string());
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());
        assert_eq!("0101", clone.to_string());
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

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
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(true);
        appendage.push(true);
        bits.append(&appendage);
        assert_eq!("1111", bits.to_string());
        assert_eq!(4, bits.len());
        assert_eq!(8, bits.capacity());

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
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("11", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("11", bits.to_string());
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());
        assert_eq!("1111", clone.to_string());
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

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
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        appendage.push(false);
        appendage.push(false);
        bits.append(&appendage);
        assert_eq!("0000", bits.to_string());
        assert_eq!(4, bits.len());
        assert_eq!(8, bits.capacity());

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
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("00", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("00", bits.to_string());
        assert_eq!(2, bits.len());
        assert_eq!(8, bits.capacity());
        assert_eq!("0000", clone.to_string());
        assert_eq!(4, clone.len());
        assert_eq!(8, clone.capacity());

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
        } // 4 bytes, +3 bits
        assert_eq!("1111111111111111111111111111", bits.to_string());
        assert_eq!(28, bits.len());
        assert_eq!(32, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0..7 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("11111111111111111111111111111111111", bits.to_string());
        assert_eq!(35, bits.len());
        assert_eq!(40, bits.capacity());

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
        assert_eq!(35, clone.len());
        assert_eq!(40, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("11", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("111111111111111111111111111111111", bits.to_string());
        assert_eq!(33, bits.len());
        assert_eq!(40, bits.capacity());
        assert_eq!("11111111111111111111111111111111111", clone.to_string());
        assert_eq!(35, clone.len());
        assert_eq!(40, clone.capacity());

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
        } // 4 bytes, +3 bits
        assert_eq!("00000000000000000000000000", bits.to_string());
        assert_eq!(26, bits.len());
        assert_eq!(32, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0..9 {
            appendage.push(false);
        }
        bits.append(&appendage);
        assert_eq!("00000000000000000000000000000000000", bits.to_string());
        assert_eq!(35, bits.len());
        assert_eq!(40, bits.capacity());

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
        assert_eq!(35, clone.len());
        assert_eq!(40, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("00", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("000000000000000000000000000000000", bits.to_string());
        assert_eq!(33, bits.len());
        assert_eq!(40, bits.capacity());
        assert_eq!("00000000000000000000000000000000000", clone.to_string());
        assert_eq!(35, clone.len());
        assert_eq!(40, clone.capacity());

        /* test is_empty */
        assert_eq!(false, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }
}
