package htree

// todo
import "fmt"

type HuffNode struct {
	Left *HuffNode
	Right *HuffNode

	Symbol rune
	Frequency uint64
}

type HuffmanTree struct {
	Root *HuffNode
}

type count struct {
	freq uint64
}

func Create(input string) HuffmanTree {
	var frequencies = toFrequencyMap(input)
	var nodes = toSlice(frequencies)

	fmt.Println(len(frequencies))
	fmt.Println(len(nodes))

	var tree HuffmanTree
	return tree
}

func toFrequencyMap(input string) map[rune]count {
	frequencies := make(map[rune]count)
	runes := []rune(input)
	for i := 0; i < len(runes); i++ {
		var letter = runes[i]

		if _, ok := frequencies[letter]; ok {
			var oldCount = frequencies[letter]
			newCount := count{ freq: oldCount.freq + 1 }
			frequencies[letter] = newCount
		} else {
			newCount := count { freq: 1 }
			frequencies[letter] = newCount
		}
	}

	//for k, v := range frequencies {
	//	fmt.Printf("key[%q] value[%d]\n", k, v)
	//}

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
