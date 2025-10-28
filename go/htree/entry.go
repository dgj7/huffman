package htree

import "errors"
import "math"

type Entry struct {
	key BitSet
	value byte

	left *Entry
	right *Entry
}

func NewLeaf(theKey BitSet, theValue byte) *Entry {
	return &Entry { key: theKey, value: theValue, left: nil, right: nil }
}

func InsertEntry(e *Entry, theKey BitSet, theValue byte) bool {
	if theKey.LessThan(e.key) {
		//fmt.Printf("\t%s(%d) < %s(%d),", theKey.ToString(), theKey.ToUint64(), e.key.ToString(), e.key.ToUint64())
		if e.left == nil {
			//fmt.Printf("new leaf, left\n")
			e.left = NewLeaf(theKey, theValue)
			return true
		} else {
			//fmt.Printf("calling on e.left\n")
			return InsertEntry(e.left, theKey, theValue)
		}
	} else if theKey.Equals(e.key) {
		//fmt.Printf("\treturn false, %s already exists\n", theKey.ToString())
		return false
	} else {
		//fmt.Printf("\t%s(%d) > %s(%d),", theKey.ToString(), theKey.ToUint64(), e.key.ToString(), e.key.ToUint64())
		if e.right == nil {
			//fmt.Printf("new leaf, right\n")
			e.right = NewLeaf(theKey, theValue)
			return true
		} else {
			//fmt.Printf("calling on e.right\n")
			return InsertEntry(e.right, theKey, theValue)
		}
	}
}

func FindEntry(e *Entry, theKey BitSet) (byte, error) {
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
			return FindEntry(e.left, theKey)
		}
	} else if theKey.Equals(e.key) {
		return e.value, nil
	} else {
		if e.right == nil {
			return 0, errors.New("no byte found for " + theKey.ToString())
		} else {
			return FindEntry(e.right, theKey)
		}
	}
}

func EntrySize(e *Entry) int {
	if e == nil {
		return 0
	}

	var left = EntrySize(e.left)
	var right = EntrySize(e.right)

	return 1 + left + right
}

func EntryHeight(e *Entry) int {
	if e == nil {
		return 0
	}

	var left = EntryHeight(e.left)
	var right = EntryHeight(e.right)

	return 1 + int(math.Max(float64(left), float64(right)))
}
