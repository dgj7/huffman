///
/// Convert input String into byte [Vector].
///
pub fn string_to_bytes(message : &str) -> Vec<u8> {
    let mut vec = vec!();

    for c in message.chars() {
        vec.push(c as u8);
    }

    return vec;
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

    return sb;
}

#[cfg(test)]
mod test {
    use crate::translator::{bytes_to_message, string_to_bytes};

    #[test]
    fn test_string_to_bytes() {
        let message = "Hello World!".to_string();
        let bytes = string_to_bytes(&message);

        assert_eq!(12, bytes.len());
        assert_eq!(72, bytes[0]);
        assert_eq!(101, bytes[1]);
        assert_eq!(108, bytes[2]);
        assert_eq!(108, bytes[3]);
        assert_eq!(111, bytes[4]);
        assert_eq!(32, bytes[5]);
        assert_eq!(87, bytes[6]);
        assert_eq!(111, bytes[7]);
        assert_eq!(114, bytes[8]);
        assert_eq!(108, bytes[9]);
        assert_eq!(100, bytes[10]);
        assert_eq!(33, bytes[11]);
    }

    #[test]
    fn test_bytes_to_string() {
        let bytes = vec![72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33];
        let message = bytes_to_message(&bytes);

        assert_eq!(String::from("Hello World!"), message);
    }
}
