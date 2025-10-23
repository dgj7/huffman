package htree

import "strings"

type BitSet struct {
	data []uint8
}

func NewBitSet(len int) BitSet {
	return BitSet { data: make([]uint8, len) }
}

func MergeBitSets(left BitSet, right BitSet) BitSet {
	var lenSum int = left.Len() + right.Len()
	var bs = NewBitSet(lenSum)

	var i int = 0
	for i < left.Len() {
			var value bool = left.GetBit(i)
			bs.SetBit(i, value)
			i = i + 1
	}

	i = 0
	for i < right.Len() {
		var value bool = right.GetBit(i)
		bs.SetBit(left.Len() + i, value)
		i = i + 1
	}

	return bs
}

func (bs BitSet) Len() int {
	return len(bs.data)
}

func (bs BitSet) GetBit(index int) bool {
	var position = index / 8
	var shift = uint(index % 8)
	return (bs.data[position] & (uint8(1) << shift)) != 0
}

func (bs BitSet) SetBit(index int, value bool) {
	var position = index / 8
	var shift = uint(index % 8)
	if value {
		bs.data[position] |= (uint8(1) << shift)
	} else {
		bs.data[position] &= ^(uint8(1) << shift)
	}
}

func (bs BitSet) ToString() string {
	var sb strings.Builder

	var i int = 0
	for i < len(bs.data) {
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
