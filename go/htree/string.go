package htree

import "unicode/utf8"

func StringToBytes(message string) []byte {
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

func BytesToString(bytes []byte) string {
	var message = ""
	for len(bytes) > 0 {
		theRune, _ := utf8.DecodeRune(bytes)
		message += string(theRune)
		bytes = bytes[1:]
	}
	return message
}
