package htree

//import "fmt"

type Table struct {
	root *Entry
}

func NewTable() Table {
	return Table { root: nil }
}

func (t *Table) Insert(theKey BitSet, theValue byte) bool {
	//fmt.Printf("inserting %s(%d)\n", theKey.ToString(), theKey.ToUint64())
	if t.root == nil {
		//fmt.Printf("\tnew root: %s\n", theKey.ToString())
		t.root = NewLeaf(theKey, theValue)
		return true
	} else {
		return InsertEntry(t.root, theKey, theValue)
	}

	return false
}

func (t Table) Find(theKey BitSet) (byte, error) {
	return FindEntry(t.root, theKey)
}

func (t Table) Size() int {
	return EntrySize(t.root)
}

func (t Table) Height() int {
	return EntryHeight(t.root)
}
