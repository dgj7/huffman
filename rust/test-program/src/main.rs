use std::fmt::{Display, Formatter};
use bitvec::macros::internal::funty::Fundamental;
use bitvec::prelude::BitVec;
use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::frequencies_to_tree;
use huffman_coding_lib::count_frequencies;

extern crate huffman_coding_lib;

fn main() {
    let start = std::time::Instant::now();
    let input = parse(std::env::args());

    let bytes = string_to_bytes(&input);
    let frequencies = count_frequencies(&bytes);
    let tree = frequencies_to_tree(&frequencies);
    let mut encoded = encode(&frequencies, &tree);
    let decoded = decode(&mut encoded, tree);
    let translated = bytes_to_message(&decoded);

    println!("input:   [{}]", input);
    println!("encoded: [{}]", PrintableBitVec::new(&encoded));
    println!("decoded: [{}]", translated);
    println!("done. ({}ms)", start.elapsed().as_millis());
}

fn parse(args: std::env::Args) -> String {
    let args_vec: Vec<String> = args.collect();
    if args_vec.len() == 3 && args_vec[1] == "-i" {
        return args_vec[2].to_string();
    } else {
        panic!("bad args; expected -i only")
    }
}

///
/// Convert input String into byte [Vector].
///
pub fn string_to_bytes(message : &String) -> Vec<u8> {
    let mut vec = vec!();

    for c in message.chars() {
        vec.push(c as u8);
    }

    return vec;
}

///
/// Translate output byte [Vector] into String.
///
pub fn bytes_to_message(bytes : &Vec<u8>) -> String {
    let mut sb = String::new();

    for b in bytes {
        let c = *b as char;
        sb.push(c);
    }

    return sb;
}

struct PrintableBitVec {
    bits: BitVec,
}

impl PrintableBitVec {
    pub(crate) fn new(the_bits: &BitVec) -> PrintableBitVec {
        PrintableBitVec { bits: the_bits.clone() }
    }
}

impl Display for PrintableBitVec {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.bits.iter().for_each(|bit| {
            value.push_str(bit.as_u8().to_string().as_str());
        });
        write!(f, "{}", value)
    }
}

#[cfg(test)]
mod test {
    use huffman_coding_lib::{count_frequencies, decode, encode, frequencies_to_tree};
    use crate::{bytes_to_message, string_to_bytes, PrintableBitVec};

    #[test]
    fn test_main_scenario() {
        let mut input = String::new();
        input.push_str("this is a sample input string. its text is being used to test the huffman coding tree.");

        let bytes = string_to_bytes(&input);
        let frequencies = count_frequencies(&bytes);
        let tree = frequencies_to_tree(&frequencies);

        let mut encoded = encode(&frequencies, &tree);
        assert_eq!(339, encoded.len());
        assert_eq!(String::from("100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010"), String::from(PrintableBitVec::new(&encoded).to_string()));

        let decoded = decode(&mut encoded, tree);
        let translated = bytes_to_message(&decoded);
        assert_eq!("this is a sample input string. its text is being used to test the huffman coding tree.", translated);
    }

    #[test]
    fn test_string_to_bytes() {
        let message = "Hello World!".to_string();
        let bytes = string_to_bytes(&message);

        assert_eq!(12, bytes.len());
        assert_eq!(72, bytes[0]);
        assert_eq!(101, bytes[1]);
        assert_eq!(108, bytes[2]);
        assert_eq!(108, bytes[3]);
        assert_eq!(111, bytes[4]);
        assert_eq!(32, bytes[5]);
        assert_eq!(87, bytes[6]);
        assert_eq!(111, bytes[7]);
        assert_eq!(114, bytes[8]);
        assert_eq!(108, bytes[9]);
        assert_eq!(100, bytes[10]);
        assert_eq!(33, bytes[11]);
    }

    #[test]
    fn test_bytes_to_string() {
        let bytes = vec![72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33];
        let message = bytes_to_message(&bytes);

        assert_eq!(String::from("Hello World!"), message);
    }
}
