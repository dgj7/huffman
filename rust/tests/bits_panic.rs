#[cfg(test)]
mod test {
    use huffman_coding_lib::bits::Bits;

    #[test]
    #[should_panic(expected="ERROR: EXTRACT: start(0) >= bit_length(0)")]
    fn test_extract_start_out_of_range() {
        let mut bits = Bits::new();

        /* test extract */
        bits.extract(0, 1);
    }

    #[test]
    #[should_panic(expected="ERROR: EXTRACT: count(7) > bit_length(6)")]
    fn test_extract_count_out_of_range() {
        let mut bits = Bits::new();

        /* test push */
        for _ in 0 .. 6 {
            bits.push(true);
        }

        /* test extract */
        bits.extract(0, 7);
    }
}
