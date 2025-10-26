package htree

import "strings"
import "math/big"
import "fmt"

type BitSet struct {
	data []byte
	bitLength int
}

// todo: reverse method

func NewBitSet(byteCount int) BitSet {
	return BitSet { data: make([]byte, byteCount), bitLength: 0 }
}

func MergeBitSets(left BitSet, right BitSet) BitSet {
	/* determine the correct size for the merged bitset */
	var bitLength int = left.Len() + right.Len()
	var byteLength = (bitLength / 8) + 1
	var bs = NewBitSet(byteLength)

	/* copy left bitset's values */
	var lx = 0;
	for lx < left.Len() {
		var value = left.GetBit(lx)
		bs.Append(value)
		lx = lx + 1
	}

	/* copy right bitset's values */
	var rx = 0
	for rx < right.Len() {
		var value = right.GetBit(rx)
		bs.Append(value)
		rx = rx + 1
	}

	/* done */
	return bs
}

func (bs BitSet) Len() int {
	return bs.bitLength
}

func (bs BitSet) GetBit(bitIndex int) bool {
	/* determine where the new data needs to live */
	var byteLength = len(bs.data)
	var byteIndex = bitIndex / 8
	var shift = uint(bitIndex % 8)

	/* handle bad byte index */
	if byteIndex >= byteLength {
		var message = fmt.Sprintf("GetBit(%d): byteLength=[%d]\n", byteIndex, byteLength)
		panic(message)
	}

	/* read and return the data */
	return (bs.data[byteIndex] & (byte(1) << shift)) != 0
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

func (bs *BitSet) SetBit(bitIndex int, value bool) {
	/* determine where the new data needs to live */
	var byteLength = len(bs.data)
	var byteIndex = bitIndex / 8
	var shift = uint(bitIndex % 8)

	/* handle bad byte index */
	if byteIndex >= byteLength {
		var message = fmt.Sprintf("SetBit(%d,%t): byteLength=[%d]\n", byteIndex, value, byteLength)
		panic(message)
	}

	/* write to the correct bit/byte index */
	if value {
		bs.data[byteIndex] |= (byte(1) << shift)
	} else {
		bs.data[byteIndex] &= ^(byte(1) << shift)
	}
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

func (bs BitSet) ToUint64() uint64 {
	if len(bs.data) == 0 {
		return 0
	}

	return big.NewInt(0).SetBytes(bs.data).Uint64()
}
