package htree

type HuffTree struct {
	Root *HuffNode
}

func (tree HuffTree) size() uint64 {
	return tree.Root.size()
}

func (tree HuffTree) ToEncodingTable() map[rune]BitSet {
	var output = make(map[rune]BitSet)
	descendTree(tree, output, tree.size())
	return output
}

// todo: this should not be using the stringified version of the bitset
func (tree HuffTree) ToDecodingTable() map[string]rune {
	var encoding = tree.ToEncodingTable()
	var decoding = make(map[string]rune)

	for k, v := range encoding {
		decoding[v.ToString()] = k
	}

	return decoding
}

func descendTree(tree HuffTree, table map[rune]BitSet, capacity uint64) {
	if tree.Root.Left != nil {
		descendNode(tree.Root.Left, capacity, 0, false, make([]bool, capacity), table)
	}
	if tree.Root.Right != nil {
		descendNode(tree.Root.Right, capacity, 0, true, make([]bool, capacity), table)
	}
}
