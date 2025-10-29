package htree

func Encode(tree HuffTree, input []byte) BitSet {
	var output = NewBitSet(0)
	var table = tree.ToEncodingTable()

	for _, char := range input {
		if bs, ok := table[char]; ok {
			output = MergeBitSets(output, bs)
		} else {
			// todo: panic?
		}
	}

	return output
}
