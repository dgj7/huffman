extern crate huffman_coding_lib;
mod translator;
mod printable;

use crate::translator::{bytes_to_message, string_to_bytes};
use crate::printable::PrintableBitVec;
use huffman_coding_lib::count_frequencies;
use huffman_coding_lib::decode;
use huffman_coding_lib::encode;
use huffman_coding_lib::frequencies_to_tree;

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

#[cfg(test)]
mod test {
    use crate::translator::{bytes_to_message, string_to_bytes};
    use huffman_coding_lib::{count_frequencies, decode, encode, frequencies_to_tree};

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
}
