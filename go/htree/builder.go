package htree

import "sort"

func Create(input string) HuffTree {
	var frequencies = toFrequencyMap(input)
	var nodes = toSlice(frequencies)
	return toTree(nodes)
}

func toFrequencyMap(input string) map[rune]int {
	frequencies := make(map[rune]int)

	if (len(input) == 0) {
		return frequencies
	}

	runes := []rune(input)
	for i := 0; i < len(runes); i++ {
		var letter = runes[i]

		if oldCount, ok := frequencies[letter]; ok {
			newCount := oldCount + 1
			frequencies[letter] = newCount
		} else {
			newCount := 1
			frequencies[letter] = newCount
		}
	}

	return frequencies
}

func toSlice(input map[rune]int) []HuffNode {
	output := make([]HuffNode, 0)
	
	for k, v := range input {
		node := HuffNode { Symbol: k, Frequency: v }
		output = append(output, node)
	}

	return output
}

func toTree(input []HuffNode) HuffTree {
	if (len(input) == 0) {
		return HuffTree { Root: nil }
	}

	for len(input) > 1 {
		/* sort the list */
		sort.Sort(NodeArray(input))

		/* print some debug info */
		//DebugNodeSlice(input)

		/* pull the first two elements */
		var left = input[0]
		var right = input[1]

		/* resize the array */
		input = append(input[:0], input[2:]...)

		/* merge the first two elements into a tree */
		var root = HuffNode { Left: &left, Right: &right, Frequency: left.Frequency + right.Frequency }

		/* add the tree back to the list */
		input = append(input, root)
	}
	return HuffTree { Root: &input[0] }
}
