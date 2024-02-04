mod input;
mod node;
mod tree;
mod encoded;
mod decoded;
mod debug;

fn main() {
    let input = input::StringInput::new(std::env::args());
    let tree = tree::HuffmanTree::new(&input);
    let encoded = encoded::Encoded::new(&input, &tree);
    let decoded = decoded::Decoded::new(&encoded, &tree);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", encoded);
    println!("decoded: [{}]", decoded);
}

#[cfg(test)]
mod tests_e2e {
    use crate::input::StringInput;
    use crate::tree::HuffmanTree;

    #[test]
    fn test() {
        let input = StringInput { message: "this is a sample input string. its text is being used to test the huffman coding tree.".to_string() };
        let tree = HuffmanTree::new(&input);

        assert_eq!(21, tree.encodings.len());
        assert_eq!(41, tree.root.size());
        assert_eq!("011010", format!("{:?}", tree.encodings.get(&'b').unwrap())); // frequency: 1
        assert_eq!("011011", format!("{:?}", tree.encodings.get(&'c').unwrap())); // frequency: 1
        assert_eq!("101000", format!("{:?}", tree.encodings.get(&'l').unwrap())); // frequency: 1
        assert_eq!("101001", format!("{:?}", tree.encodings.get(&'x').unwrap())); // frequency: 1
        assert_eq!("110010", format!("{:?}", tree.encodings.get(&'.').unwrap())); // frequency: 2
        assert_eq!("110011", format!("{:?}", tree.encodings.get(&'d').unwrap())); // frequency: 2
        assert_eq!("01000", format!("{:?}", tree.encodings.get(&'f').unwrap()));  // frequency: 2
        assert_eq!("01001", format!("{:?}", tree.encodings.get(&'m').unwrap()));  // frequency: 2
        assert_eq!("01010", format!("{:?}", tree.encodings.get(&'o').unwrap()));  // frequency: 2
        assert_eq!("01011", format!("{:?}", tree.encodings.get(&'p').unwrap()));  // frequency: 2
        assert_eq!("01100", format!("{:?}", tree.encodings.get(&'r').unwrap()));  // frequency: 2
        assert_eq!("10101", format!("{:?}", tree.encodings.get(&'a').unwrap()));  // frequency: 3
        assert_eq!("10110", format!("{:?}", tree.encodings.get(&'g').unwrap()));  // frequency: 3
        assert_eq!("10111", format!("{:?}", tree.encodings.get(&'h').unwrap()));  // frequency: 3
        assert_eq!("11000", format!("{:?}", tree.encodings.get(&'u').unwrap()));  // frequency: 3
        assert_eq!("0111", format!("{:?}", tree.encodings.get(&'n').unwrap()));   // frequency: 5
        assert_eq!("1101", format!("{:?}", tree.encodings.get(&'e').unwrap()));   // frequency: 8
        assert_eq!("000", format!("{:?}", tree.encodings.get(&'i').unwrap()));    // frequency: 8
        assert_eq!("001", format!("{:?}", tree.encodings.get(&'s').unwrap()));    // frequency: 8
        assert_eq!("100", format!("{:?}", tree.encodings.get(&'t').unwrap()));    // frequency: 11
        assert_eq!("111", format!("{:?}", tree.encodings.get(&' ').unwrap()));    // frequency: 16
    }
}
