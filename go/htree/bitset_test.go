package htree

import "testing"
import "github.com/stretchr/testify/assert" // https://pkg.go.dev/github.com/stretchr/testify/assert

func TestBitSet_EmptyZeroBits(t *testing.T) {
	var bs = NewBitSet(0)

	assert.Equal(t, "", bs.ToString())
}

func TestBitSet_EmptyOneBit(t *testing.T) {
	var bs = NewBitSet(1)

	assert.Equal(t, "", bs.ToString())
}
