package main

import "fmt"
import "flag"
import "os"
import "gohuff/htree"

func main() {
	var input = loadInput()
	var tree = htree.Create(input)
	var encoded = htree.Encode(tree, input)
	var decoded = htree.Decode(tree, encoded)

	fmt.Printf("input:   [%s]\n", input)
	fmt.Printf("encoded: [%s]\n", htree.Stringify(encoded))
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
