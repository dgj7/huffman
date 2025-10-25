package htree

type HuffNode struct {
	Left *HuffNode
	Right *HuffNode

	Symbol rune
	Frequency int
}

func (node HuffNode) size() int {
	var leftSize int = 0
	if node.Left != nil {
		leftSize = node.Left.size()
	}

	var rightSize int = 0
	if node.Right != nil {
		rightSize = node.Right.size()
	}

	return 1 + leftSize + rightSize
}

func (node HuffNode) isLeaf() bool {
	return node.Left == nil && node.Right == nil
}

func descendNode(node *HuffNode, index int, next bool, bs []bool, table map[rune]BitSet) {
	bs[index] = next
	if (node.Left != nil && node.Right != nil) {
		descendNode(node.Left, index + 1, false, bs, table)
		descendNode(node.Right, index + 1, true, bs, table)
	} else {
		bitset := NewBitSet(index+1)
		var i int = 0
		for i < index+1 {
			var b = bs[i]
			bitset.SetBit(i, b)
			i = i + 1
		}
		//fmt.Printf("%c ===> %s\n", node.Symbol, bitset.ToString())
		table[node.Symbol] = bitset
	}
}
