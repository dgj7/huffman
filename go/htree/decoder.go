package htree

func Decode(tree HuffTree, encoded BitSet) []byte {
	var result = make([]byte, 0)
	var key = ""
	var table = tree.ToDecodingTable()

	var i int = 0

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
			result = append(result, char)
			key = ""
		}

		i = i + 1
	}

	return result
}
