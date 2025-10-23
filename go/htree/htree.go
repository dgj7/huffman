package htree

type HuffTree struct {
	Root *HuffNode
}

func treeSize(tree HuffTree) uint64 {
	return nodeSize(tree.Root)
}

func (tree HuffTree) ToEncodingTable() map[rune]BitSet {
	var output = make(map[rune]BitSet)
	var capacity = uint64(MaxDepth(tree.Root))
	descendTree(tree, output, capacity)
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
