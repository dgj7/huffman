package main

import "fmt"
import "flag"
import "os"
import "unicode/utf8"

import "gohuff/htree"

func main() {
	var input = loadInput()

	//var asBytes = stringToBytes(input)
	//fmt.Printf("[%s]\n", string(asBytes))
	//var asChars = bytesToString(asBytes)
	//fmt.Printf("[%s]\n", asChars)

	var tree = htree.Create(input)
	var encoded = htree.Encode(tree, input)
	var decoded = htree.Decode(tree, encoded)

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

func stringToBytes(message string) []byte {
	var totalLength = len(message)
	var bytes = make([]byte, totalLength)
	for c := 0; c < totalLength; c++ {
		theRune, size := utf8.DecodeRuneInString(message)
		if size > 1 {
			panic("invalid character")
		}
		bytes[c] = byte(theRune)
		message = message[size:]
	}
	return bytes
}

func bytesToString(bytes []byte) string {
	var message = ""
	for len(bytes) > 0 {
		theRune, _ := utf8.DecodeRune(bytes)
		message += string(theRune)
		bytes = bytes[1:]
	}
	return message
}
