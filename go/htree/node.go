package htree

type HuffNode struct {
	Left *HuffNode
	Right *HuffNode

	Symbol rune
	Frequency uint64
}

func (node HuffNode) size() uint64 {
	var leftSize uint64 = 0
	if node.Left != nil {
		leftSize = node.Left.size()
	}

	var rightSize uint64 = 0
	if node.Right != nil {
		rightSize = node.Right.size()
	}

	return 1 + leftSize + rightSize
}

func (node HuffNode) isLeaf() bool {
	return node.Left == nil && node.Right == nil
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
		//fmt.Printf("%c ===> %s\n", node.Symbol, bitset.ToString())
		table[node.Symbol] = bitset
	}
}
