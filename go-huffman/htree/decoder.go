package htree

func Decode(tree HuffTree, encoded BitSet) string {
	var result = ""
	var node = tree.Root;

	var i uint64 = 0

	for i < encoded.Len() {
		var bit = encoded.GetBit(i)

		if !bit && node.Right != nil {
			node = node.Right
		} else if bit && node.Left != nil {
			node = node.Left
		} else {
			result = result + string(node.Symbol)
			node = tree.Root
		}

		i = i + 1
	}

	return result
}
