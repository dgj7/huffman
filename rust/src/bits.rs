use std::fmt::{Display, Formatter};

///
/// Data structure for storage and access to an array of bits.
///
#[derive(Clone)]
pub struct Bits {
    storage: Vec<u8>,
    bit_capacity: usize,
    bit_length: usize,
}

///
/// Iterate over [Bits], one bit at a time.
///
pub struct BitsIterator<'a> {
    bits: &'a Bits,
    bit_index: usize,
}

///
/// Iterate over [Bits], one byte at a time.
///
pub struct BytesIterator<'a> {
    bits: &'a Bits,
    byte_index: usize,
    max: usize,
}

///
/// Bits implementation.
///
impl Bits {
    ///
    /// Create a new instance, with no bits.
    ///
    pub fn new() -> Self {
        Self {
            storage: Vec::new(),
            bit_capacity: 0,
            bit_length: 0,
        }
    }

    ///
    /// Push the given bits to the end of the vector.
    ///
    pub fn push(&mut self, bit: bool) {
        /* initialize storage, if needed */
        if self.bit_capacity <= self.bit_length {
            self.storage.push(0);
            self.bit_capacity += 8;
        }

        /* increment length for the next call */
        self.bit_length += 1;

        /* write the bit to the byte */
        self.write(self.bit_length - 1, bit);
    }

    ///
    /// Append the given [Bits] to this.
    pub fn append(&mut self, other: &Bits) {
        other.iter().for_each(|bit| {
            self.push(bit);
        });
    }

    ///
    /// Iterate over bits.
    ///
    pub fn iter(&self) -> BitsIterator<'_> {
        BitsIterator {
            bits: self,
            bit_index: 0,
        }
    }

    ///
    /// Iterate over bytes.
    ///
    pub fn bytes_iter(&self) -> BytesIterator<'_> {
        BytesIterator {
            bits: self,
            byte_index: 0,
            max: self.storage.len(),
        }
    }

    ///
    /// Extract (start, start+count-1) bits and return as a new [Bits].
    ///
    pub fn extract(&mut self, start: usize, count: usize) -> Bits {
        /* storage for output */
        let mut bits = Bits::new();

        /* sc if count < 1 */
        if count < 1 {
            return bits;
        }

        /* panic if state illegal */
        if start >= self.bit_length {
            panic!(
                "ERROR: EXTRACT: [start({})] >= [bit_length({})]",
                start, self.bit_length
            );
        }

        /* iterate over all bits, copying (count) bits for output, and shifting all bits */
        for (counter, current_index) in (start..self.bit_length).enumerate() {
            /* if this is a bit that we need to copy over, grab it */
            if counter < count {
                let current_bit = self.read(current_index);
                bits.push(current_bit);
            }

            /* locate the replacement bit */
            let replacement_index = current_index + count;
            let replacement_bit = if replacement_index > self.bit_length - 1 {
                false
            } else {
                self.read(replacement_index)
            };

            /* overwrite the current bit with the replacement bit */
            self.write(current_index, replacement_bit);
        }

        /* remove (zero) the last 'count' bits */
        for remove_index in (self.bit_capacity - count)..self.bit_capacity {
            self.write(remove_index, false);
        }

        /* update size */
        self.bit_length -= count;

        /* determine if any storage bytes can be freed */
        let needed_storage_bytes = self.bit_capacity / 8;
        let mut actual_storage_bytes = self.storage.len();
        while needed_storage_bytes < actual_storage_bytes {
            self.storage.remove(actual_storage_bytes - 1);
            actual_storage_bytes -= 1;
        }

        /* update capacity; must always be multiple of 8 */
        self.bit_capacity = if self.bit_length == 0 {
            0
        } else {
            actual_storage_bytes * 8
        };

        /* done */
        bits
    }

    ///
    /// Determine if the array is empty.
    ///
    pub fn is_empty(&self) -> bool {
        self.bit_length == 0
    }

    ///
    /// Determine length.
    ///
    pub fn len(&self) -> usize {
        self.bit_length
    }

    ///
    /// Determine capacity.
    ///
    pub fn capacity(&self) -> usize {
        self.bit_capacity
    }

    ///
    /// Read/return the bit at the given read index.
    ///
    /// NOT the byte index.
    ///
    pub(crate) fn read(&self, read_index: usize) -> bool {
        /* validate that read_index is within bounds */
        if read_index >= self.bit_length {
            panic!(
                "ERROR: READ: [read_index({})] >= [bit_length({})]",
                read_index, self.bit_length
            );
        }

        /* determine and validate the byte index */
        let byte_index = read_index / 8;
        if byte_index >= self.storage.len() {
            panic!(
                "ERROR: READ: [byte_index({})] >= [byte_capacity({})]",
                byte_index,
                self.storage.len()
            );
        }

        /* determine and validate the bit index */
        let bit_index = read_index % 8;
        if bit_index >= 8 {
            panic!("ERROR: READ: [bit_index({})] >= 8", bit_index);
        }

        /* load the byte */
        let byte = self.storage[byte_index];

        /* done */
        byte >> bit_index & 1 == 1
    }

    ///
    /// Write the given bit to the given write index.
    ///
    /// NOT the byte index.
    ///
    pub(crate) fn write(&mut self, write_index: usize, bit: bool) {
        /* validate that write is within bounds */
        if write_index >= self.bit_capacity {
            panic!(
                "ERROR: WRITE: [write_index({})] >= [bit_length({})]",
                write_index, self.bit_length
            );
        }

        /* determine and validate the byte index */
        let byte_index = write_index / 8;
        if byte_index >= self.storage.len() {
            panic!(
                "ERROR: WRITE: [byte_index({})] >= [byte_capacity({})]",
                byte_index,
                self.storage.len()
            );
        }

        /* determine and validate the bit index */
        let bit_index = write_index % 8;
        if bit_index >= 8 {
            panic!("ERROR: WRITE: [bit_index({})] >= 8", bit_index);
        }

        /* load the byte */
        let byte = &mut self.storage[byte_index];

        /* write data */
        Self::write_helper(byte, bit_index, bit);
    }

    ///
    /// Helper function for write().
    ///
    // todo: attempt to integrate this into the write() method.
    fn write_helper(byte: &mut u8, bit_index: usize, bit: bool) {
        let mask: u8 = !(1 << bit_index);
        let flag: u8 = (bit as u8) << bit_index;

        *byte &= mask;
        *byte |= flag;
    }
}

impl<'a> Iterator for BitsIterator<'a> {
    type Item = bool;

    fn next(&mut self) -> Option<Self::Item> {
        if self.bit_index < self.bits.bit_length {
            let result = self.bits.read(self.bit_index);
            self.bit_index += 1;
            Some(result)
        } else {
            None
        }
    }
}

impl<'a> Iterator for BytesIterator<'a> {
    type Item = u8;

    fn next(&mut self) -> Option<Self::Item> {
        let prior_byte_index = self.byte_index;
        self.byte_index += 1;
        if prior_byte_index < self.max {
            Some(self.bits.storage[prior_byte_index])
        } else {
            None
        }
    }
}

impl Display for Bits {
    fn fmt(&self, f: &mut Formatter) -> std::fmt::Result {
        let mut value = String::new();
        self.iter().for_each(|bit| {
            let num = bit as u8;
            value.push_str(num.to_string().as_str());
        });
        write!(f, "{}", value)
    }
}

impl Default for Bits {
    fn default() -> Self {
        Self::new()
    }
}
