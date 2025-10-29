package htree

type HuffTree struct {
	Root *HuffNode
}

func (tree HuffTree) size() int {
	if tree.Root == nil {
		return 0
	}
	
	return tree.Root.size()
}

func (tree HuffTree) ToEncodingTable() map[byte]BitSet {
	var output = make(map[byte]BitSet)

	if (tree.Root == nil) {
		return output
	}

	descendTree(tree, output)
	return output
}

func (tree HuffTree) ToDecodingTable() Table {
	var encoding = tree.ToEncodingTable()
	var decoding = NewTable()

	for k, v := range encoding {
		decoding.Insert(v, k)
	}

	return decoding
}

func descendTree(tree HuffTree, table map[byte]BitSet) {
	if tree.Root.Left != nil {
		descendNode(tree.Root.Left, 0, false, make([]bool, tree.size()), table)
	}
	if tree.Root.Right != nil {
		descendNode(tree.Root.Right, 0, true, make([]bool, tree.size()), table)
	}
}

func descendNode(node *HuffNode, index int, next bool, bs []bool, table map[byte]BitSet) {
	bs[index] = next
	if (node.Left != nil && node.Right != nil) {
		descendNode(node.Left, index + 1, false, bs, table)
		descendNode(node.Right, index + 1, true, bs, table)
	} else {
		bitset := NewBitSet(index+1)
		var i int = 0
		for i < index+1 {
			var b = bs[i]
			bitset.Append(b)
			i = i + 1
		}
		//fmt.Printf("%c ===> %s\n", node.Symbol, bitset.ToString())
		table[node.Symbol] = bitset
	}
}
