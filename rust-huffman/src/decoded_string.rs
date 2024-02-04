use std::fmt;
use bitvec::vec::BitVec;
use crate::encoded::Encoded;
use crate::tree::HuffmanTree;

pub struct DecodedString {
    pub message: String,
}

impl DecodedString {
    pub fn new(encoded: &mut Encoded, maybe_tree: &Option<HuffmanTree>) -> DecodedString {
        if maybe_tree.is_none() {
            return DecodedString { message: String::new() };
        }
        let tree = maybe_tree.as_ref().unwrap();

        let mut builder = String::new();
        let mut bits = encoded.bits.clone();

        while !bits.is_empty() {
            let db = tree.next_decoded(&bits, &tree.root, 0, BitVec::new());
            bits.drain(0..db.bits.len());
            builder.push(db.symbol);
        }

        DecodedString { message: builder }
    }
}

impl fmt::Display for DecodedString {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}

#[cfg(test)]
mod tests {
    use crate::decoded_string::DecodedString;
    use crate::encoded::Encoded;
    use crate::input::StringInput;
    use crate::tree::HuffmanTree;

    #[test]
    fn test_case1() {
        let input: &StringInput = &StringInput::from_message("this is a sample input string. its text is being used to test the huffman coding tree.".to_string());
        let tree = HuffmanTree::new(input);
        let mut encoded = Encoded::new(input, &tree);
        let decoded = DecodedString::new(&mut encoded, &tree);

        assert_eq!("this is a sample input string. its text is being used to test the huffman coding tree.", decoded.message);
    }
}
