#[cfg(test)]
mod test {
    use huffman_coding_lib::bits::Bits;

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
        assert_eq!(11, bits.len());
        assert_eq!(16, bits.capacity());

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
        assert_eq!(20, bits.len());
        assert_eq!(24, bits.capacity());

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
        assert_eq!(20, clone.len());
        assert_eq!(24, clone.capacity());

        /* test extract */
        let extracted = bits.extract(1, 2);
        assert_eq!("01", extracted.to_string());
        assert_eq!(2, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("101010101101010101", bits.to_string());
        assert_eq!(18, bits.len());
        assert_eq!(24, bits.capacity());
        assert_eq!("10101010101101010101", clone.to_string());
        assert_eq!(20, clone.len());
        assert_eq!(24, clone.capacity());

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
        assert_eq!(16, bits.len());
        assert_eq!(16, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 3 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("1111111111111111111", bits.to_string());
        assert_eq!(19, bits.len());
        assert_eq!(24, bits.capacity());

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
        assert_eq!(19, clone.len());
        assert_eq!(24, clone.capacity());

        /* test extract */
        let extracted = bits.extract(10, 3);
        assert_eq!("111", extracted.to_string());
        assert_eq!(3, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("1111111111111111", bits.to_string());
        assert_eq!(16, bits.len());
        assert_eq!(24, bits.capacity());
        assert_eq!("1111111111111111111", clone.to_string());
        assert_eq!(19, clone.len());
        assert_eq!(24, clone.capacity());

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
        assert_eq!(7, bits.len());
        assert_eq!(8, bits.capacity());

        /* test append */
        let mut appendage = Bits::new();
        for _ in 0 .. 1 {
            appendage.push(true);
        }
        bits.append(&appendage);
        assert_eq!("11111111", bits.to_string());
        assert_eq!(8, bits.len());
        assert_eq!(8, bits.capacity());

        /* test bytes iterator */
        let mut byte_iterator = bits.bytes_iter();
        let byte1 = byte_iterator.next().unwrap();
        let byte2 = byte_iterator.next();
        assert_eq!(255, byte1);
        assert_eq!(None, byte2);

        /* test clone */
        let clone = bits.clone();
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.len());
        assert_eq!(8, clone.capacity());

        /* test extract */
        let extracted = bits.extract(0, 8);
        assert_eq!("11111111", extracted.to_string());
        assert_eq!(8, extracted.len());
        assert_eq!(8, extracted.capacity());
        assert_eq!("", bits.to_string());
        assert_eq!(0, bits.len());
        assert_eq!(0, bits.capacity());
        assert_eq!("11111111", clone.to_string());
        assert_eq!(8, clone.len());
        assert_eq!(8, clone.capacity());

        /* test is_empty */
        assert_eq!(true, bits.is_empty());
        assert_eq!(false, appendage.is_empty());
        assert_eq!(false, clone.is_empty());
        assert_eq!(false, extracted.is_empty());
    }
}
