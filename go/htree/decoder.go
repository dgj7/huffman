package htree

func Decode(tree HuffTree, encoded BitSet) []byte {
	var result = make([]byte, 0)
	var key = NewBitSet(0)
	var table = tree.ToDecodingTable()

	var i int = 0

	for i < encoded.Len() {
		var bit = encoded.GetBit(i)
		key.Append(bit)

		char, ok := table.Find(key)
		if ok {
			result = append(result, char)
			key = NewBitSet(0)
		}

		i = i + 1
	}

	return result
}
