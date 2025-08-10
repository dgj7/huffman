#[cfg(test)]
mod test {
    use huffman_coding_lib::translator::{bytes_to_string, string_to_bytes};
    use huffman_coding_lib::{count_frequencies, decode, encode, frequencies_to_tree};

    #[test]
    fn test_end_to_end_1() {
        let input = String::from("this is a sample input string. its text is being used to test the huffman coding tree.");
        let expected = String::from("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010");

        let bytes = string_to_bytes(&input);
        let frequencies = count_frequencies(&bytes);
        let tree = frequencies_to_tree(&frequencies);
        let mut encoded = encode(&frequencies, &tree);
        let decoded = decode(&mut encoded, tree);
        let translated = bytes_to_string(&decoded);

        assert_eq!("this is a sample input string. its text is being used to test the huffman coding tree.", translated);
        assert_eq!(86, translated.len());

        assert_eq!(expected, encoded.to_string());
        assert_eq!(339, encoded.len());
    }
}
