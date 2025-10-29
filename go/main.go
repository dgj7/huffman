package main

import "fmt"
import "flag"
import "os"

import "gohuff/htree"

func main() {
	var input = loadInput()
	var bytes = htree.StringToBytes(input)
	var tree = htree.Create(bytes)
	var encoded = htree.Encode(tree, bytes)
	var decodedBytes = htree.Decode(tree, encoded)
	var decoded = htree.BytesToString(decodedBytes)

	//htree.DebugPrintEncodingTable(tree)
	//htree.DebugPrintDecodingTable(tree)

	fmt.Printf("input:   [%s]\n", input)
	fmt.Printf("encoded: [%s]\n", encoded.ToString())
	fmt.Printf("decoded: [%s]\n", decoded)
}

func loadInput() string {
	var input string
	flag.StringVar(&input, "i", "", "the input value")
	flag.Parse()

	if input == "" {
		fmt.Fprintf(os.Stderr, "missing required argument -i\n")
		os.Exit(2)
	}

	return input
}
