use crate::tree::*;
use std::collections::HashMap;
use std::fmt;

// todo: see if this can be replaced with a simple method

///
/// Convert input data into [Vec]tor of [TreeNode]s.
///
pub trait FrequencyProcessor {
    fn to_frequencies(&self) -> Vec<TreeNode>;
    fn to_bytes(&self) -> Vec<u8>;
}

///
/// [FrequencyProcessor] implementation for u8 [Vec] input.
///
pub struct DefaultFrequencyProcessor {
    message: Vec<u8>,
}

impl DefaultFrequencyProcessor {
    pub fn new(the_message: &Vec<u8>) -> DefaultFrequencyProcessor {
        DefaultFrequencyProcessor {
            message: the_message.to_owned(),
        }
    }
}

impl FrequencyProcessor for DefaultFrequencyProcessor {
    fn to_frequencies(&self) -> Vec<TreeNode> {
        let mut map: HashMap<u8, usize> = HashMap::new();
        let mut vec = vec![];

        self.message.iter().for_each(|symbol| {
            let value = if map.contains_key(&symbol) {
                let temp: &usize = &map.get(&symbol).unwrap().to_owned();
                temp + 1
            } else {
                1
            };

            map.insert(*symbol, value);
        });

        map.iter()
            .for_each(|elem| vec.push(TreeNode::new_leaf(*elem.0, *elem.1)));

        vec
    }

    fn to_bytes(&self) -> Vec<u8> {
        self.message.clone()
    }
}

impl fmt::Display for DefaultFrequencyProcessor {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{:?}", self.message)
    }
}
