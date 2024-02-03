use std::collections::HashMap;
use std::fmt;

pub(crate) struct Input {
    //
}

impl Input {
    pub fn new(args: std::env::Args) -> Input {
        Input{}
    }

    pub fn to_hash_map(&self) -> HashMap<char, usize> {
        panic!("not yet implemented")
    }
}

impl fmt::Display for Input {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // todo
        write!(f, "")
    }
}
