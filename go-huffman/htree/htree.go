package htree

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
	var _ = determineFrequencies(input)

	var tree HuffmanTree
	return tree
}

func determineFrequencies(input string) map[rune]count {
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
