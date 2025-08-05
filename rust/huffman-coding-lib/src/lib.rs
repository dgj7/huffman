use ::bitvec::vec::BitVec;
use crate::encoding::*;
use crate::tree::*;
use crate::frequency::*;

pub mod debug;
pub mod encoding;
pub mod frequency;
pub mod tree;

pub fn count_frequencies(message: &Vec<u8>) -> impl FrequencyProcessor {
    return DefaultFrequencyProcessor::new(&message);
}

pub fn frequencies_to_tree(input: &impl FrequencyProcessor) -> Option<HuffmanTree> {
    return HuffmanTree::new(input);
}

pub fn encode(input: &impl FrequencyProcessor, tree: &Option<HuffmanTree>) -> BitVec {
    return do_encode(input, &tree);
}

pub fn decode(encoded: &mut BitVec, tree: Option<HuffmanTree>) -> Vec<u8> {
    return do_decode(encoded, &tree);
}
