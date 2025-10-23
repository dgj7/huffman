package htree

type HuffTree struct {
	Root *HuffNode
}

func (tree HuffTree) size() int {
	if tree.Root == nil {
		return 0
	}
	
	return tree.Root.size()
}

func (tree HuffTree) ToEncodingTable() map[rune]BitSet {
	var output = make(map[rune]BitSet)

	if (tree.Root == nil) {
		return output
	}

	descendTree(tree, output)
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

func descendTree(tree HuffTree, table map[rune]BitSet) {
	if tree.Root.Left != nil {
		descendNode(tree.Root.Left, 0, false, make([]bool, tree.size()), table)
	}
	if tree.Root.Right != nil {
		descendNode(tree.Root.Right, 0, true, make([]bool, tree.size()), table)
	}
}
