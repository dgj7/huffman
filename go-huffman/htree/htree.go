package htree

import "sort"

type HuffNode struct {
	Left *HuffNode
	Right *HuffNode

	Symbol rune
	Frequency uint64
}

type HuffTree struct {
	Root *HuffNode
}

type count struct {
	freq uint64
}

func Create(input string) HuffTree {
	var frequencies = toFrequencyMap(input)
	var nodes = toSlice(frequencies)
	return toTree(nodes)
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

func toFrequencyMap(input string) map[rune]count {
	frequencies := make(map[rune]count)
	runes := []rune(input)
	for i := 0; i < len(runes); i++ {
		var letter = runes[i]

		if oldCount, ok := frequencies[letter]; ok {
			newCount := count{ freq: oldCount.freq + 1 }
			frequencies[letter] = newCount
		} else {
			newCount := count { freq: 1 }
			frequencies[letter] = newCount
		}
	}

	return frequencies
}

func toSlice(input map[rune]count) []HuffNode {
	output := make([]HuffNode, 0)
	
	for k, v := range input {
		node := HuffNode { Symbol: k, Frequency: v.freq }
		output = append(output, node)
	}

	return output
}

func toTree(input []HuffNode) HuffTree {
	for len(input) > 1 {
		/* sort the list */
		sort.Slice(input, func(lex, rix int) bool {
			var le = input[lex]
			var ri = input[rix]
			if le.Frequency == ri.Frequency {
				if isLeaf(&le) && isLeaf(&ri) {
					return le.Symbol < ri.Symbol
				} else {
					return nodeSize(&le) < nodeSize(&ri)
				}
			} else {
				return le.Frequency < ri.Frequency
			}
		})

		/* pull the first two elements */
		var left = input[0]
		var right = input[1]

		/* shorten the slice */
		input = removeFromSlice(input, 0)
		input = removeFromSlice(input, 0)

		/* merge the first two elements into a tree */
		var root = HuffNode { Left: &left, Right: &right, Frequency: left.Frequency + right.Frequency }

		/* add the tree back to the list */
		input = append(input, root)
	}
	return HuffTree { Root: &input[0] }
}

func removeFromSlice(s []HuffNode, index int) []HuffNode {
    return append(s[:index], s[index+1:]...)
}

func treeSize(tree HuffTree) uint64 {
	return nodeSize(tree.Root)
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

func (tree HuffTree) ToEncodingTable() map[rune]BitSet {
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
