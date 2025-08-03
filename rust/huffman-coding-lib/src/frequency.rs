use core::str::Chars;
use std::fmt;
use std::collections::HashMap;

use crate::tree::*;

///
/// Convert input data into [Vec]tor of [TreeNode]s.
///
pub trait FrequencyProcessor {
    fn to_vector(&self) -> Vec<TreeNode>;
    fn to_char_array(&self) -> Chars;
}

///
/// [FrequencyProcessor] implementation for [String] input.
///
pub struct StringFrequencyProcessor {
    message: String,
}

impl StringFrequencyProcessor {
    pub fn new(the_message: &String) -> StringFrequencyProcessor {
        StringFrequencyProcessor { message: the_message.to_string() }
    }
}

impl FrequencyProcessor for StringFrequencyProcessor {
    fn to_vector(&self) -> Vec<TreeNode> {
        let mut map: HashMap<char, usize> = HashMap::new();
        let mut vec = vec!();

        self.message
            .chars()
            .for_each(|symbol| {
                let value = if map.contains_key(&symbol) {
                    let temp: &usize = &map.get(&symbol).unwrap().to_owned();
                    temp + 1
                } else {
                    1
                };

                map.insert(symbol, value);
            });

        map.iter().for_each(|elem| vec.push(TreeNode::new_leaf(*elem.0, *elem.1)));

        return vec;
    }

    fn to_char_array(&self) -> Chars {
        self.message.chars().into_iter()
    }
}

impl fmt::Display for StringFrequencyProcessor {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}
