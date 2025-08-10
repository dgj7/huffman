///
/// Convert input String into byte [Vector].
///
pub fn string_to_bytes(message : &str) -> Vec<u8> {
    let mut vec = vec!();

    for c in message.chars() {
        vec.push(c as u8);
    }

    vec
}

///
/// Translate output byte [Vector] into String.
///
pub fn bytes_to_message(bytes : &Vec<u8>) -> String {
    let mut sb = String::new();

    for b in bytes {
        let c = *b as char;
        sb.push(c);
    }

    sb
}
