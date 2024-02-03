use std::collections::HashMap;
use std::fmt;

pub trait Input {
    fn to_hash_map(&self) -> HashMap<char, usize>;
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
    fn to_hash_map(&self) -> HashMap<char, usize> {
        let mut map = HashMap::new();

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

        //map.iter().for_each(|elem| println!("[{}]=>[{}]", elem.0, elem.1));

        return map;
    }
}

impl fmt::Display for StringInput {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.message)
    }
}
