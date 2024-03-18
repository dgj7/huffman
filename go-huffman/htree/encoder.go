package htree

import "unicode/utf8"

func Encode(tree HuffTree, input string) BitSet {
	var messageLength = uint64(utf8.RuneCountInString(input))
	var output = NewBitSet(messageLength)
	var table = toEncodingTable(tree)

	for _, char := range input {
		if bs, ok := table[char]; ok {
			output = MergeBitSets(output, bs)
		} else {
			// todo: panic?
		}
	}

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
		descendNode(tree.Root.Left, capacity, 0, false, make([]bool, capacity), table)
	}
	if tree.Root.Right != nil {
		descendNode(tree.Root.Right, capacity, 0, true, make([]bool, capacity), table)
	}
}

func descendNode(node *HuffNode, capacity uint64, index uint64, next bool, bs []bool, table map[rune]BitSet) {
	bs[index] = next
	if (node.Left != nil && node.Right != nil) {
		descendNode(node.Left, capacity, index + 1, false, bs, table)
		descendNode(node.Right, capacity, index + 1, true, bs, table)
	} else {
		bitset := NewBitSet(index+1)
		var i uint64 = 0
		for i < index+1 {
			var b = bs[i]
			bitset.SetBit(i, b)
			i = i + 1
		}
		table[node.Symbol] = bitset
	}
}
