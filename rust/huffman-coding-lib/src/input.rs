use core::str::Chars;
use std::fmt;
use std::collections::HashMap;

use crate::node::TreeNode;

pub trait Input {
    fn to_vector(&self) -> Vec<TreeNode>;
    fn to_char_array(&self) -> Chars;
}

pub struct StringInput {
    pub message: String,
}

impl StringInput {
    pub fn new(the_message: &String) -> StringInput {
        StringInput { message: the_message.to_string() }
    }
}

impl Input for StringInput {
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

impl fmt::Display for StringInput {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}
