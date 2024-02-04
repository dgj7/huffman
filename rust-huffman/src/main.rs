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
    use crate::{decoded_string, encoded};
    use crate::input::StringInput;
    use crate::tree::HuffmanTree;

    #[test]
    fn test_e2e_empty() {
        let input = StringInput { message: "".to_string() };
        let maybe_tree = HuffmanTree::new(&input);

        assert_eq!(false, maybe_tree.is_some());

        let mut encoded = encoded::Encoded::new(&input, &maybe_tree);
        let decoded = decoded_string::DecodedString::new(&mut encoded, &maybe_tree);

        assert_eq!(0, encoded.bits.len());
        assert_eq!("", decoded.message);
    }

    #[test]
    fn test_e2e_case1() {
        let input = StringInput { message: "this is a sample input string. its text is being used to test the huffman coding tree.".to_string() };
        let maybe_tree = HuffmanTree::new(&input);

        assert_eq!(true, maybe_tree.is_some());
        let tree = maybe_tree.as_ref().unwrap();
        let encodings = &tree.encodings;
        let root = &tree.root;

        assert_eq!(21, encodings.len());
        assert_eq!(41, root.size());
        assert_eq!("011010", format!("{}", PrintableBitVec::new(encodings.get(&'b').unwrap()))); // frequency: 1
        assert_eq!("011011", format!("{}", PrintableBitVec::new(encodings.get(&'c').unwrap()))); // frequency: 1
        assert_eq!("101000", format!("{}", PrintableBitVec::new(encodings.get(&'l').unwrap()))); // frequency: 1
        assert_eq!("101001", format!("{}", PrintableBitVec::new(encodings.get(&'x').unwrap()))); // frequency: 1
        assert_eq!("110010", format!("{}", PrintableBitVec::new(encodings.get(&'.').unwrap()))); // frequency: 2
        assert_eq!("110011", format!("{}", PrintableBitVec::new(encodings.get(&'d').unwrap()))); // frequency: 2
        assert_eq!("01000", format!("{}", PrintableBitVec::new(encodings.get(&'f').unwrap())));  // frequency: 2
        assert_eq!("01001", format!("{}", PrintableBitVec::new(encodings.get(&'m').unwrap())));  // frequency: 2
        assert_eq!("01010", format!("{}", PrintableBitVec::new(encodings.get(&'o').unwrap())));  // frequency: 2
        assert_eq!("01011", format!("{}", PrintableBitVec::new(encodings.get(&'p').unwrap())));  // frequency: 2
        assert_eq!("01100", format!("{}", PrintableBitVec::new(encodings.get(&'r').unwrap())));  // frequency: 2
        assert_eq!("10101", format!("{}", PrintableBitVec::new(encodings.get(&'a').unwrap())));  // frequency: 3
        assert_eq!("10110", format!("{}", PrintableBitVec::new(encodings.get(&'g').unwrap())));  // frequency: 3
        assert_eq!("10111", format!("{}", PrintableBitVec::new(encodings.get(&'h').unwrap())));  // frequency: 3
        assert_eq!("11000", format!("{}", PrintableBitVec::new(encodings.get(&'u').unwrap())));  // frequency: 3
        assert_eq!("0111", format!("{}", PrintableBitVec::new(encodings.get(&'n').unwrap())));   // frequency: 5
        assert_eq!("1101", format!("{}", PrintableBitVec::new(encodings.get(&'e').unwrap())));   // frequency: 8
        assert_eq!("000", format!("{}", PrintableBitVec::new(encodings.get(&'i').unwrap())));    // frequency: 8
        assert_eq!("001", format!("{}", PrintableBitVec::new(encodings.get(&'s').unwrap())));    // frequency: 8
        assert_eq!("100", format!("{}", PrintableBitVec::new(encodings.get(&'t').unwrap())));    // frequency: 11
        assert_eq!("111", format!("{}", PrintableBitVec::new(encodings.get(&' ').unwrap())));    // frequency: 16
    }
}
