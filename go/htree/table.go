package htree

import "errors"

//import "fmt"

type Entry struct {
	key BitSet
	value byte

	left *Entry
	right *Entry
}

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
		t.root = newLeaf(theKey, theValue)
		return true
	} else {
		return insertHelper(t.root, theKey, theValue)
	}

	return false
}

func (t Table) Find(theKey BitSet) (byte, error) {
	return findHelper(t.root, theKey)
}

func newLeaf(theKey BitSet, theValue byte) *Entry {
	return &Entry { key: theKey, value: theValue, left: nil, right: nil }
}

func insertHelper(e *Entry, theKey BitSet, theValue byte) bool {
	if theKey.LessThan(e.key) {
		//fmt.Printf("\t%s(%d) < %s(%d),", theKey.ToString(), theKey.ToUint64(), e.key.ToString(), e.key.ToUint64())
		if e.left == nil {
			//fmt.Printf("new leaf, left\n")
			e.left = newLeaf(theKey, theValue)
			return true
		} else {
			//fmt.Printf("calling on e.left\n")
			return insertHelper(e.left, theKey, theValue)
		}
	} else if theKey.Equals(e.key) {
		//fmt.Printf("\treturn false, %s already exists\n", theKey.ToString())
		return false
	} else {
		//fmt.Printf("\t%s(%d) > %s(%d),", theKey.ToString(), theKey.ToUint64(), e.key.ToString(), e.key.ToUint64())
		if e.right == nil {
			//fmt.Printf("new leaf, right\n")
			e.right = newLeaf(theKey, theValue)
			return true
		} else {
			//fmt.Printf("calling on e.right\n")
			return insertHelper(e.right, theKey, theValue)
		}
	}
}

func findHelper(e *Entry, theKey BitSet) (byte, error) {
	if e == nil {
		return 0, errors.New("table is empty")
	}

	if e.key.Equals(theKey) {
		return e.value, nil
	}

	if theKey.LessThan(e.key) {
		if e.left == nil {
			return 0, errors.New("no byte found for " + theKey.ToString())
		} else {
			return findHelper(e.left, theKey)
		}
	} else if theKey.Equals(e.key) {
		return e.value, nil
	} else {
		if e.right == nil {
			return 0, errors.New("no byte found for " + theKey.ToString())
		} else {
			return findHelper(e.right, theKey)
		}
	}
}
