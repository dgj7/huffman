#[cfg(test)]
mod test {
    use huffman_coding_lib::bits::Bits;

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
        assert_eq!(0, clone.len());
        assert_eq!(0, clone.capacity());

        /* test extract */
        let extracted = bits.extract(0, 0);
        assert_eq!("", extracted.to_string());
        assert_eq!(0, extracted.len());
        assert_eq!(0, extracted.capacity());
        assert_eq!("", bits.to_string());
        assert_eq!(0, bits.len());
        assert_eq!(0, bits.capacity());
        assert_eq!("", clone.to_string());
        assert_eq!(0, clone.len());
        assert_eq!(0, clone.capacity());

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
}
