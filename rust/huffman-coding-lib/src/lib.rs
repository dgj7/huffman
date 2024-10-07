use crate::encoding::*;
use crate::tree::*;
use crate::frequency::*;

pub mod bitvec;
pub mod debug;
pub mod encoding;
pub mod frequency;
pub mod tree;

pub fn count_frequencies(message: &String) -> impl FrequencyProcessor {
    return StringFrequencyProcessor::new(&message);
}

pub fn frequencies_to_tree(input: &impl FrequencyProcessor) -> Option<HuffmanTree> {
    return HuffmanTree::new(input);
}

pub fn encode(input: &impl FrequencyProcessor, tree: &Option<HuffmanTree>) -> Encoded {
    return Encoded::new(input, &tree);
}

pub fn decode(encoded: &mut Encoded, tree: Option<HuffmanTree>) -> DecodedString {
    return DecodedString::new(encoded, &tree);
}
