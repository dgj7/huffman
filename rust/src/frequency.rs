use std::collections::HashMap;
use crate::tree::TreeNode;

///
/// Count the frequency of each byte in the input [Vec] of [u8], returning a [Vec] of [TreeNode]s.
///
/// Note that a [Vec] of [TreeNode]s is not a [HuffmanTree].
///
pub(crate) fn count_frequencies(bytes: &[u8]) -> Vec<TreeNode> {
    let mut map: HashMap<u8, usize> = HashMap::new();
    let mut vec = vec![];

    bytes.iter().for_each(|symbol| {
        let value = if map.contains_key(symbol) {
            let temp: &usize = &map.get(symbol).unwrap().to_owned();
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
