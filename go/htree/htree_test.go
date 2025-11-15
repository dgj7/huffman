package htree

import "testing"
import "github.com/stretchr/testify/assert" // https://pkg.go.dev/github.com/stretchr/testify/assert

func TestTree_Empty(t *testing.T) {
	var input = ""
	var bytes = StringToBytes(input)

	var tree = Create(bytes)

	assert.Equal(t, 0, tree.size(), "tree size wrong")
	assert.Nil(t, tree.Root, "tree root not nil")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 0, len(encodings), "encodings len wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "", decoded, "decoded wrong")
}

func TestTree_SingleByte(t *testing.T) {
	var input = "f"
	var bytes = StringToBytes(input)

	var tree = Create(bytes)
	assert.Equal(t, 3, tree.size(), "tree size wrong")
	assert.Equal(t, 3, tree.Root.size(), "node size wrong")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 2, len(encodings), "encodings len wrong")
	assert.Equal(t, "0", encodings['f'].ToString(), "encoding wrong")
	assert.Equal(t, "1", encodings['g'].ToString(), "encoding wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "0", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "f", decoded, "decoded wrong")
}

func TestTree_TwoBytesSame(t *testing.T) {
	var input = "aa"
	var bytes = StringToBytes(input)

	var tree = Create(bytes)
	assert.Equal(t, 3, tree.size(), "tree size wrong")
	assert.Equal(t, 3, tree.Root.size(), "node size wrong")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 2, len(encodings), "encodings len wrong")
	assert.Equal(t, "0", encodings['a'].ToString(), "encoding wrong")
	assert.Equal(t, "1", encodings['b'].ToString(), "encoding wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "00", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "aa", decoded, "decoded wrong")
}

func TestTree_TwoBytesDiff(t *testing.T) {
	var input = "ab"
	var bytes = StringToBytes(input)

	var tree = Create(bytes)
	assert.Equal(t, 3, tree.size(), "tree size wrong")
	assert.Equal(t, 3, tree.Root.size(), "node size wrong")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 2, len(encodings), "encodings len wrong")
	assert.Equal(t, "0", encodings['a'].ToString(), "encoding wrong")
	assert.Equal(t, "1", encodings['b'].ToString(), "encoding wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "01", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "ab", decoded, "decoded wrong")
}

func TestTree_Short(t *testing.T) {
	var input = "abbccc"
	var bytes = StringToBytes(input)

	var tree = Create(bytes)
	assert.Equal(t, 5, tree.size(), "tree size wrong")
	assert.Equal(t, 5, tree.Root.size(), "node size wrong")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 3, len(encodings), "encodings len wrong")
	assert.Equal(t, "10", encodings['a'].ToString(), "encoding wrong")
	assert.Equal(t, "11", encodings['b'].ToString(), "encoding wrong")
	assert.Equal(t, "0", encodings['c'].ToString(), "encoding wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "101111000", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "abbccc", decoded, "decoded wrong")
}

func TestTree_MainCase(t *testing.T) {
	var input = "this is a sample input string. its text is being used to test the huffman coding tree.";
	var bytes = StringToBytes(input)

	var tree = Create(bytes)
	assert.Equal(t, 41, tree.size(), "tree size wrong")
	assert.Equal(t, 41, tree.Root.size(), "tree node size wrong")

	var encodings = tree.ToEncodingTable()
	assert.Equal(t, 21, len(encodings), "encodings len wrong")
	assert.Equal(t, "01010", encodings['o'].ToString(), "encoding wrong")
    assert.Equal(t, "01100", encodings['r'].ToString(), "encoding wrong")
    assert.Equal(t, "0111", encodings['n'].ToString(), "encoding wrong")
    assert.Equal(t, "011011", encodings['c'].ToString(), "encoding wrong")
    assert.Equal(t, "111", encodings[' '].ToString(), "encoding wrong")
    assert.Equal(t, "01001", encodings['m'].ToString(), "encoding wrong")
    assert.Equal(t, "101000", encodings['l'].ToString(), "encoding wrong")
    assert.Equal(t, "10101", encodings['a'].ToString(), "encoding wrong")
    assert.Equal(t, "11000", encodings['u'].ToString(), "encoding wrong")
    assert.Equal(t, "110011", encodings['d'].ToString(), "encoding wrong")
    assert.Equal(t, "000", encodings['i'].ToString(), "encoding wrong")
    assert.Equal(t, "100", encodings['t'].ToString(), "encoding wrong")
    assert.Equal(t, "011010", encodings['b'].ToString(), "encoding wrong")
    assert.Equal(t, "10110", encodings['g'].ToString(), "encoding wrong")
    assert.Equal(t, "10111", encodings['h'].ToString(), "encoding wrong")
    assert.Equal(t, "110010", encodings['.'].ToString(), "encoding wrong")
    assert.Equal(t, "01000", encodings['f'].ToString(), "encoding wrong")
    assert.Equal(t, "01011", encodings['p'].ToString(), "encoding wrong")
    assert.Equal(t, "101001", encodings['x'].ToString(), "encoding wrong")
    assert.Equal(t, "1101", encodings['e'].ToString(), "encoding wrong")
    assert.Equal(t, "001", encodings['s'].ToString(), "encoding wrong")

	var encoded = Encode(tree, bytes)
	assert.Equal(t, "100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010", encoded.ToString(), "encoded wrong")

	var decodedBytes = Decode(tree, encoded)
	var decoded = BytesToString(decodedBytes)
	assert.Equal(t, "this is a sample input string. its text is being used to test the huffman coding tree.", decoded, "decoded wrong")
}
