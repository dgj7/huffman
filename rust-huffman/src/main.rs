mod input;
mod node;
mod tree;
mod encoded;
mod decoded_string;
mod debug;
mod decoded_byte;
mod bitvec;

fn main() {
    let start = std::time::Instant::now();
    let input = input::StringInput::new(std::env::args());
    let tree = tree::HuffmanTree::new(&input);
    let mut encoded = encoded::Encoded::new(&input, &tree);
    let decoded = decoded_string::DecodedString::new(&mut encoded, &tree);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded);
    println!("decoded: [{}]", decoded);
    println!("done. ({}ms)", start.elapsed().as_millis());
}

#[cfg(test)]
mod tests_e2e {
    use crate::bitvec::PrintableBitVec;
    use crate::input::StringInput;
    use crate::tree::HuffmanTree;

    #[test]
    fn test() {
        let input = StringInput { message: "this is a sample input string. its text is being used to test the huffman coding tree.".to_string() };
        let tree = HuffmanTree::new(&input);

        assert_eq!(21, tree.encodings.len());
        assert_eq!(41, tree.root.size());
        assert_eq!("011010", format!("{}", PrintableBitVec::new(tree.encodings.get(&'b').unwrap()))); // frequency: 1
        assert_eq!("011011", format!("{}", PrintableBitVec::new(tree.encodings.get(&'c').unwrap()))); // frequency: 1
        assert_eq!("101000", format!("{}", PrintableBitVec::new(tree.encodings.get(&'l').unwrap()))); // frequency: 1
        assert_eq!("101001", format!("{}", PrintableBitVec::new(tree.encodings.get(&'x').unwrap()))); // frequency: 1
        assert_eq!("110010", format!("{}", PrintableBitVec::new(tree.encodings.get(&'.').unwrap()))); // frequency: 2
        assert_eq!("110011", format!("{}", PrintableBitVec::new(tree.encodings.get(&'d').unwrap()))); // frequency: 2
        assert_eq!("01000", format!("{}", PrintableBitVec::new(tree.encodings.get(&'f').unwrap())));  // frequency: 2
        assert_eq!("01001", format!("{}", PrintableBitVec::new(tree.encodings.get(&'m').unwrap())));  // frequency: 2
        assert_eq!("01010", format!("{}", PrintableBitVec::new(tree.encodings.get(&'o').unwrap())));  // frequency: 2
        assert_eq!("01011", format!("{}", PrintableBitVec::new(tree.encodings.get(&'p').unwrap())));  // frequency: 2
        assert_eq!("01100", format!("{}", PrintableBitVec::new(tree.encodings.get(&'r').unwrap())));  // frequency: 2
        assert_eq!("10101", format!("{}", PrintableBitVec::new(tree.encodings.get(&'a').unwrap())));  // frequency: 3
        assert_eq!("10110", format!("{}", PrintableBitVec::new(tree.encodings.get(&'g').unwrap())));  // frequency: 3
        assert_eq!("10111", format!("{}", PrintableBitVec::new(tree.encodings.get(&'h').unwrap())));  // frequency: 3
        assert_eq!("11000", format!("{}", PrintableBitVec::new(tree.encodings.get(&'u').unwrap())));  // frequency: 3
        assert_eq!("0111", format!("{}", PrintableBitVec::new(tree.encodings.get(&'n').unwrap())));   // frequency: 5
        assert_eq!("1101", format!("{}", PrintableBitVec::new(tree.encodings.get(&'e').unwrap())));   // frequency: 8
        assert_eq!("000", format!("{}", PrintableBitVec::new(tree.encodings.get(&'i').unwrap())));    // frequency: 8
        assert_eq!("001", format!("{}", PrintableBitVec::new(tree.encodings.get(&'s').unwrap())));    // frequency: 8
        assert_eq!("100", format!("{}", PrintableBitVec::new(tree.encodings.get(&'t').unwrap())));    // frequency: 11
        assert_eq!("111", format!("{}", PrintableBitVec::new(tree.encodings.get(&' ').unwrap())));    // frequency: 16
    }
}
