package htree

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
		if e.left == nil {
			e.left = NewLeaf(theKey, theValue)
			return true
		} else {
			return InsertEntry(e.left, theKey, theValue)
		}
	} else if theKey.Equals(e.key) {
		return false
	} else {
		if e.right == nil {
			e.right = NewLeaf(theKey, theValue)
			return true
		} else {
			return InsertEntry(e.right, theKey, theValue)
		}
	}
}

func FindEntry(e *Entry, theKey BitSet) (byte, bool) {
	if e == nil {
		return 0, false
	}

	if e.key.Equals(theKey) {
		return e.value, true
	}

	if theKey.LessThan(e.key) {
		if e.left == nil {
			return 0, false
		} else {
			return FindEntry(e.left, theKey)
		}
	} else {
		if e.right == nil {
			return 0, false
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
