package htree

type HuffNode struct {
	Left *HuffNode
	Right *HuffNode

	Symbol rune
	Frequency uint64
}

func MaxDepth(input *HuffNode) int {
	if input == nil {
		return 0
	}

	var leftDepth int = MaxDepth(input.Left)
	var rightDepth int = MaxDepth(input.Right)

	if leftDepth > rightDepth {
		return leftDepth +1
	} else {
		return rightDepth +1
	}
}

func nodeSize(root *HuffNode) uint64 {
	if root == nil {
		return 0
	}

	var leftSize uint64 = 0
	if root.Left != nil {
		leftSize = nodeSize(root.Left)
	}

	var rightSize uint64 = 0
	if root.Right != nil {
		rightSize = nodeSize(root.Right)
	}

	return 1 + leftSize + rightSize
}

func isLeaf(node *HuffNode) bool {
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
