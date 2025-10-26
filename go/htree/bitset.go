package htree

import "strings"

type BitSet struct {
	data []byte
	bitLength int
}

func NewBitSet(byteCount int) BitSet {
	return BitSet { data: make([]byte, byteCount), bitLength: 0 }
}

func MergeBitSets(left BitSet, right BitSet) BitSet {
	// todo: this isn't hte right length; needs to be BYTES and not BITS
	var lenSum int = left.Len() + right.Len()
	var bs = NewBitSet(lenSum)

	var lx = 0;
	for lx < left.Len() {
		var value = left.GetBit(lx)
		bs.Append(value)
		lx = lx + 1
	}

	var rx = 0
	for rx < right.Len() {
		var value = right.GetBit(rx)
		bs.Append(value)
		rx = rx + 1
	}

	return bs
}

func (bs BitSet) Len() int {
	return bs.bitLength
}

func (bs BitSet) GetBit(index int) bool {
	var position = index / 8
	var shift = uint(index % 8)
	return (bs.data[position] & (byte(1) << shift)) != 0
}

func (bs *BitSet) Append(value bool) {
	/* determine where the new data needs to live */
	var byteLength = len(bs.data)
	var bitIndex = bs.bitLength
	var byteIndex = bitIndex / 8

	/* resize the array if it's presently undersized */
	if byteIndex >= byteLength {
		bs.data = append(bs.data, 0)
	}

	/* increment the bit length */
	bs.bitLength = bs.bitLength + 1;

	/* write the next bit */
	bs.SetBit(bitIndex, value)
}

func (bs *BitSet) SetBit(index int, value bool) {
	var position = index / 8
	var shift = uint(index % 8)

	if value {
		bs.data[position] |= (byte(1) << shift)
	} else {
		bs.data[position] &= ^(byte(1) << shift)
	}
}

func (bs BitSet) ToString() string {
	var sb strings.Builder

	var i int = 0
	for i < bs.Len() {
		var value = bs.GetBit(i)
		if value {
			sb.WriteString("1")
		} else {
			sb.WriteString("0")
		}
		i = i+1
	}

	return sb.String()
}

func (bs BitSet) Equals(other BitSet) bool {
	if bs.Len() == other.Len() {
		for i := 0; i < bs.Len(); i++ {
			if bs.GetBit(i) != other.GetBit(i) {
				return false
			}
		}
		return true
	}
	return false 
}
