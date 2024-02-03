use std::collections::HashMap;
use std::fmt;
use crate::node::TreeNode;

pub trait Input {
    fn to_vector(&self) -> Vec<TreeNode>;
}

pub struct StringInput {
    pub message: String,
}

impl StringInput {
    pub fn new(args: std::env::Args) -> StringInput {
        let args_vec: Vec<String> = args.collect();
        if args_vec.len() == 3 && args_vec[1] == "-i" {
            StringInput { message: args_vec[2].to_string() }
        } else {
            panic!("bad args; expected -i only")
        }
    }
}

impl Input for StringInput {
    fn to_vector(&self) -> Vec<TreeNode> {
        let mut map = HashMap::new();
        let mut vec = vec!();

        self.message
            .chars()
            .for_each(|symbol| {
            let mut value = 0;
            if map.contains_key(&symbol) {
                value = *map.get(&symbol).unwrap() + 1;
            } else {
                value = 1;
            }
            map.insert(symbol, value);
        });

        map.iter().for_each(|elem| vec.push(TreeNode::new_leaf(*elem.0, *elem.1)));

        return vec;
    }
}

impl fmt::Display for StringInput {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}
