package htree

import "unicode/utf8"

func Encode(tree HuffTree, input string) BitSet {
	var capacity = uint64(utf8.RuneCountInString(input))
	var output = NewBitSet(capacity)
	var _ = toEncodingTable(tree)

	/*
	for pos, char := range input {
		//
	}
	*/

	return output
}

func toEncodingTable(tree HuffTree) map[rune]BitSet {
	var output = make(map[rune]BitSet)
	var capacity = uint64(MaxDepth(tree.Root))
	descendTree(tree, output, capacity)
	return output
}

func descendTree(tree HuffTree, table map[rune]BitSet, capacity uint64) {
	if tree.Root.Left != nil {
		descendNode(tree.Root.Left, false, 0, table, capacity)
	}
	if tree.Root.Right != nil {
		descendNode(tree.Root.Right, true, 0, table, capacity)
	}
}

func descendNode(node *HuffNode, next bool, index uint64, table map[rune]BitSet, capacity uint64) {
	if node.Left != nil && node.Right != nil {
		descendNode(node.Left, false, index + 1, table, capacity)
		descendNode(node.Right, true, index + 1, table, capacity)
	} else {
		_, ok := table[node.Symbol]
		if !ok {
			table[node.Symbol] = NewBitSet(capacity)
		}
		table[node.Symbol].SetBit(index, next)
	}
}
