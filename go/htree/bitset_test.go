package htree

import "testing"
import "github.com/stretchr/testify/assert" // https://pkg.go.dev/github.com/stretchr/testify/assert

import "strconv"

func TestBitSet_ZeroBits_Empty(t *testing.T) {
	var bs = NewBitSet(0)

	assert.Equal(t, 0, bs.Len())
	assert.Equal(t, "", bs.ToString())

	assert.Equal(t, "0", strconv.FormatUint(bs.ToUint64(), 10))
}

func TestBitSet_OneBit_Empty(t *testing.T) {
	var bs = NewBitSet(1)

	assert.Equal(t, 0, bs.Len())
	assert.Equal(t, "", bs.ToString())

	assert.Equal(t, "0", strconv.FormatUint(bs.ToUint64(), 10))
}

func TestBitSet_OneBit_true(t *testing.T) {
	var bs = NewBitSet(0)

	bs.Append(true)

	assert.Equal(t, 1, bs.Len())
	assert.Equal(t, "1", bs.ToString())

	assert.Equal(t, "1", strconv.FormatUint(bs.ToUint64(), 10))
}

func TestBitSet_OneBit_false(t *testing.T) {
	var bs = NewBitSet(0)

	bs.Append(false)

	assert.Equal(t, 1, bs.Len())
	assert.Equal(t, "0", bs.ToString())

	assert.Equal(t, "0", strconv.FormatUint(bs.ToUint64(), 10))
}

func TestBitSet_FiveBits_TwentyOne(t *testing.T) {
	var bs = NewBitSet(0)

	bs.Append(true)
	bs.Append(false)
	bs.Append(true)
	bs.Append(false)
	bs.Append(true)

	assert.Equal(t, 5, bs.Len())
	assert.Equal(t, "10101", bs.ToString())

	assert.Equal(t, "21", strconv.FormatUint(bs.ToUint64(), 10))
}

func TestBitSet_FiveBits_Ten(t *testing.T) {
	var bs = NewBitSet(0)

	bs.Append(false)
	bs.Append(true)
	bs.Append(false)
	bs.Append(true)
	bs.Append(false)

	assert.Equal(t, 5, bs.Len())
	assert.Equal(t, "01010", bs.ToString())

	assert.Equal(t, "10", strconv.FormatUint(bs.ToUint64(), 10))
}
