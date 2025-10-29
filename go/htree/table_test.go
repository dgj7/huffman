package htree

import "testing"
import "github.com/stretchr/testify/assert" // https://pkg.go.dev/github.com/stretchr/testify/assert

import "fmt"

func TestTable_Empty(t *testing.T) {
	var table = NewTable()
	assert.Equal(t, 0, table.Size(), "size wrong")
	assert.Equal(t, 0, table.Height(), "height wrong")

	var one = createBitSet("1")
	oneRs, oneOk := table.Find(one)
	assert.Equal(t, uint8(0), oneRs, "one result wrong")
	assert.False(t, oneOk, "one ok wrong")
}

func TestTable_Full(t *testing.T) {
	var table = createTable()
	assert.Equal(t, 7, table.Size(), "size wrong")
	assert.Equal(t, 3, table.Height(), "height wrong")

	var six = createBitSet("011")
	sixRs, sixOk := table.Find(six)
	assert.Equal(t, uint8(69), sixRs, "six result wrong")
	assert.True(t, sixOk, "six ok wrong")
}

func createBitSet(bits string) BitSet {
	var bs = NewBitSet(0)
	for _, runeValue := range bits {
		if runeValue == '0' {
			bs.Append(false)
		} else if runeValue == '1' {
			bs.Append(true)
		} else {
			var message = fmt.Sprintf("don't know what to do with [%c]\n", runeValue)
			panic(message)
		}
	}
	//fmt.Printf("created %s(%d)\n", bs.ToString(), bs.ToUint64())
	return bs
}

func createTable() Table {
	var table = NewTable()
	
	table.Insert(createBitSet("111"), byte(65))     // 7, A
	table.Insert(createBitSet("101"), byte(66))	    // 5, B
	table.Insert(createBitSet("1001"), byte(67))    // 9, C
	table.Insert(createBitSet("11"), byte(68))		// 3, D
	table.Insert(createBitSet("011"), byte(69))		// 6, E
	table.Insert(createBitSet("0001"), byte(70))	// 8, F
	table.Insert(createBitSet("0101"), byte(71))	// 10, G

	return table
}
