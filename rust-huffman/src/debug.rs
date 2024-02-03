use std::collections::HashMap;
use bit_vec::BitVec;
use crate::node::TreeNode;

pub fn debug_print(vec: &mut Vec<TreeNode>) {
    println!("----------------------------------------");
    crate::tree::sort(vec);
    println!("frequencies list has [{}] elements", vec.len());
    vec.iter().for_each(|x| {
        if x.symbol.is_some() {
            /* if it's a leaf, we print simply */
            println!("[{}] <= [{}]", x.frequency, x.symbol.unwrap());
        } else {
            /* if it's an internal node, get all of the values and print those */
            let mut all_pairs = String::new();
            debug_find_all_frequency_pairs(x, &mut all_pairs);
            println!("[{}] <= INTERNAL[{}]", x.frequency, all_pairs);
        }
    });
    println!("----------------------------------------");
}

pub fn debug_find_all_frequency_pairs(node: &TreeNode, string: &mut String) {
    if node.symbol.is_some() {
        let symbol = node.symbol.unwrap().to_string();
        if !string.is_empty() {
            string.push_str(", ");
        }
        string.push_str(&*node.frequency.to_string());
        string.push_str("|");
        string.push_str(&*symbol);
        string.push_str("");
    } else {
        if node.left.is_some() {
            debug_find_all_frequency_pairs(node.left.clone().unwrap().as_ref(), string);
        }
        if node.right.is_some() {
            debug_find_all_frequency_pairs(node.right.clone().unwrap().as_ref(), string);
        }
    }
}

pub fn debug_print_encodings(map: &HashMap<char, BitVec>) {
    map.iter().for_each(|entry| println!("[{}]:    [{:?}]", entry.0, entry.1));
}
