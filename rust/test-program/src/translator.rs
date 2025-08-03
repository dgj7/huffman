
#[allow(dead_code)]// todo: remove this, after it's used
pub fn to_bytes(message : &String) -> Vec<u8> {
    let mut vec = vec!();

    for c in message.chars() {
        vec.push(c as u8);
    }

    return vec;
}

#[allow(dead_code)]// todo: remove this, after it's used
pub fn to_string(bytes : &Vec<u8>) -> String {
    let mut sb = String::new();

    for b in bytes {
        let c = *b as char;
        sb.push(c);
    }

    return sb;
}

#[cfg(test)]
mod test {
    use crate::translator::{to_bytes, to_string};

    #[test]
    fn test_to_bytes() {
        let message = "Hello World!".to_string();
        let bytes = to_bytes(&message);

        assert_eq!(bytes.len(), 13);
        assert_eq!(bytes[0], 72);
        assert_eq!(bytes[1], 101);
        assert_eq!(bytes[2], 108);
        assert_eq!(bytes[3], 108);
        assert_eq!(bytes[4], 111);
        assert_eq!(bytes[5], 32);
        assert_eq!(bytes[6], 87);
        assert_eq!(bytes[7], 111);
        assert_eq!(bytes[8], 114);
        assert_eq!(bytes[9], 108);
        assert_eq!(bytes[10], 100);
        assert_eq!(bytes[11], 33);
        assert_eq!(bytes[12], 0);
    }

    #[test]
    fn test_to_string() {
        let bytes = vec![72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33, 0];
        let message = to_string(&bytes);

        assert_eq!(message, "Hello World!");
    }
}


