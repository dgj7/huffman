package htree

type Table struct {
	root *Entry
}

func NewTable() Table {
	return Table { root: nil }
}

func (t *Table) Insert(theKey BitSet, theValue byte) bool {
	if t.root == nil {
		t.root = NewLeaf(theKey, theValue)
		return true
	} else {
		return InsertEntry(t.root, theKey, theValue)
	}

	return false
}

func (t Table) Find(theKey BitSet) (byte, bool) {
	return FindEntry(t.root, theKey)
}

func (t Table) Size() int {
	return EntrySize(t.root)
}

func (t Table) Height() int {
	return EntryHeight(t.root)
}
