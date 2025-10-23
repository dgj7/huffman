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

func DebugNodeSlice(nodes []HuffNode) {
	fmt.Printf("list has [%d] elements\n", len(nodes))
	for _, node := range nodes {
		if node.isLeaf() {
			fmt.Printf("\t[%d] <= [%c]\n", node.Frequency, node.Symbol)
		} else {
			fmt.Printf("\t[%d] <= INTERNAL[%s]\n", node.Frequency, LeavesToOneLine(&node))
		}
	}
}

func LeavesToOneLine(node *HuffNode)string {
	if node.isLeaf() {
		return fmt.Sprintf("%d|%c", node.Frequency, node.Symbol)
	} else {
		var left = LeavesToOneLine(node.Left)
		var right = LeavesToOneLine(node.Right)
		return left + ", " + right
	}
}
