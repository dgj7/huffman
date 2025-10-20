package htree

import "fmt"

func DebugPrintEncodingTable(tree HuffTree) {
	fmt.Printf("==========\n")
	var encodings = tree.ToEncodingTable()
	for symbol, bitset := range encodings {
		fmt.Printf("[%c]  ->  [%s]\n", symbol, bitset.ToString())
	}
	fmt.Printf("==========\n")
}

func DebugPrintDecodingTable(tree HuffTree) {
	fmt.Printf("==========\n")
	var table = tree.ToDecodingTable()
	for bitstring, symbol := range table {
		fmt.Printf("[%s]  ->  [%c]\n", bitstring, symbol);
	}
	fmt.Printf("==========\n")
}
