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
	
	if leftNode.Frequency == rightNode.Frequency {
		if leftNode.isLeaf() && rightNode.isLeaf() {
			return leftNode.Symbol < rightNode.Symbol
		} else {
			return (&leftNode).size() < (&rightNode).size()
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
