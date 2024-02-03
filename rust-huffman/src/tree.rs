use crate::frequency::Input;

pub struct HuffmanTree {
    //
}

impl HuffmanTree {
    pub fn new(input: &dyn Input) -> HuffmanTree {
        let frequencies = input.to_hash_map();
        HuffmanTree{}
    }
}
