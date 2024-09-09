package htree

func Decode(tree HuffTree, encoded BitSet) string {
	var result = ""
	var key = ""
	var table = tree.ToDecodingTable()

	var i uint64 = 0

	for i < encoded.Len() {
		var bit = encoded.GetBit(i)
		bitStr := ""
		if bit {
			bitStr = "1"
		} else {
			bitStr = "0"
		}
		key = key + bitStr

		char, ok := table[key]
		if ok {
			result = result + string(char)
			key = ""
		}

		i = i + 1
	}

	return result
}
