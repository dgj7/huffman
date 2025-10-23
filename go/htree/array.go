package htree

/**
 * Typedef for sort interface.
 */
type NodeArray []HuffNode

/**
 * Len() for sort interface.
 */
func (array NodeArray) Len() int {
	return len(array)
}

/**
 * Less() for sort interface.
 */
func (array NodeArray) Less(i int, j int) bool {
	var leftNode = array[i]
	var rightNode = array[j]
	return NodeLess(leftNode, rightNode)
}

func NodeLess(leftNode HuffNode, rightNode HuffNode) bool {
	if leftNode.Frequency == rightNode.Frequency {
		if leftNode.isLeaf() && rightNode.isLeaf() {
			return leftNode.Symbol < rightNode.Symbol
		} else {
			var leftSize = (&leftNode).size()
			var rightSize = (&rightNode).size()
			if (leftSize == rightSize) {
				// todo: is there a different way to achieve this?  does this need to happen in other libraries as well?
				return NodeLess(*leftNode.Left, *rightNode.Left)
			} else {
				return leftSize < rightSize
			}
		}
	} else {
		return leftNode.Frequency < rightNode.Frequency
	}
}

/**
 * Swap() for sort interface.
 */
func (array NodeArray) Swap(i int, j int) {
	var left = array[i]
	var right = array[j]

	array[i] = right
	array[j] = left
}
