package htree

import "sort"

type count struct {
	freq uint64
}

func Create(input string) HuffTree {
	var frequencies = toFrequencyMap(input)
	var nodes = toSlice(frequencies)
	return toTree(nodes)
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
		sortNodes(input)

		/* print some debug info */
		DebugNodeSlice(input)

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

func sortNodes(input []HuffNode) {
	sort.Slice(input, func(leftIndex, rightIndex int) bool {	
		var leftNode = input[leftIndex]
		var rightNode = input[rightIndex]
		
		if leftNode.Frequency == rightNode.Frequency {
			if isLeaf(&leftNode) && isLeaf(&rightNode) {
				return leftNode.Symbol < rightNode.Symbol
			} else {
				return nodeSize(&leftNode) < nodeSize(&rightNode)
			}
		} else {
			return leftNode.Frequency < rightNode.Frequency
		}
	})
}

func removeFromSlice(s []HuffNode, index int) []HuffNode {
    return append(s[:index], s[index+1:]...)
}
