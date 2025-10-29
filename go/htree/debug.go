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
	debugPrintDecodingTableHelper(table.root)
	fmt.Printf("==========\n")
}

func debugPrintDecodingTableHelper(entry *Entry) {
	if entry != nil {
		fmt.Printf("[%s]  ->  [%c]\n", entry.key.ToString(), entry.value)
	}
	debugPrintDecodingTableHelper(entry.left)
	debugPrintDecodingTableHelper(entry.right)
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
