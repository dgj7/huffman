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
