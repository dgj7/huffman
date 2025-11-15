#[cfg(test)]
mod test {
    use huffman_coding_lib::{decode, encode, treeify};

    #[test]
    fn test_empty() {
        let input = String::from("");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        assert_eq!("", encoded.to_string());
        assert_eq!(0, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("", translated);
        assert_eq!(0, translated.len());
    }

    #[test]
    fn test_single_byte() {
        let input = String::from("f");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        assert_eq!("0", encoded.to_string());
        assert_eq!(1, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("f", translated);
        assert_eq!(1, translated.len());
    }

    #[test]
    fn test_two_bytes_same() {
        let input = String::from("aa");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        assert_eq!("00", encoded.to_string());
        assert_eq!(2, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("aa", translated);
        assert_eq!(2, translated.len());
    }

    #[test]
    fn test_two_bytes_diff() {
        let input = String::from("ab");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        assert_eq!("01", encoded.to_string());
        assert_eq!(2, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("ab", translated);
        assert_eq!(2, translated.len());
    }

    #[test]
    fn test_short() {
        let input = String::from("abcaba");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        assert_eq!("011100110", encoded.to_string());
        assert_eq!(9, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("abcaba", translated);
        assert_eq!(6, translated.len());
    }

    #[test]
    fn test_main_case() {
        let input = String::from("this is a sample input string. its text is being used to test the huffman coding tree.");
        let bytes = input.as_bytes().to_vec();

        let tree = treeify(&bytes);
        let encoded = encode(&bytes, &tree);
        let decoded = decode(&encoded, &tree);

        let expected = String::from("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010");
        assert_eq!(expected, encoded.to_string());
        assert_eq!(339, encoded.len());

        let translated = String::from_utf8_lossy(&decoded);

        assert_eq!("this is a sample input string. its text is being used to test the huffman coding tree.", translated);
        assert_eq!(86, translated.len());
    }
}
