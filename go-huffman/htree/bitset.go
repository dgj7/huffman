package htree

import "strings"

type BitSet struct {
	data []uint8
	length uint64
	capacity uint64
}

func NewBitSet(cap uint64) BitSet {
	return BitSet { data: make([]uint8, cap), length: 0, capacity: cap }
}

func (bs BitSet) Len() uint64 {
	return bs.length
}

func (bs BitSet) GetBit(idx uint64) bool {
	var position = idx / 8
	var lshift = uint64(idx%8)
	var retval = (bs.data[position] & (uint8(1) << lshift)) != 0
	return retval
}

func (bs BitSet) SetBit(idx uint64, val bool) {
	var position = idx / 8
	var lshift = uint64(idx%8)
	if val {
		bs.data[position] |= (uint8(1) << lshift)
	} else {
		bs.data[position] &= ^(uint8(1) << lshift)
	}
}

func (bs BitSet) ToString() string {
	var sb strings.Builder

	var i uint64 = 0
	for i < bs.length {
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
