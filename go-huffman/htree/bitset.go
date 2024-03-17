package htree

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

func (bs BitSet) GetBit(idx int) bool {
	var position = idx / 8
	var lshift = uint(idx%8)
	var retval = (bs.data[position] & (uint8(1) << lshift)) != 0
	return retval
}

func (bs BitSet) SetBit(idx int, val bool) {
	var position = idx / 8
	var lshift = uint(idx%8)
	if val {
		bs.data[position] |= (uint8(1) << lshift)
	} else {
		bs.data[position] &= ^(uint8(1) << lshift)
	}
}
