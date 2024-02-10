# huffman
## Purpose
huffman coding trees, implemented in various languages.

generally treated as a programming challenge, to be redone for any new language learned.

## Usage
There is a `run-all.sh` script in the root directory that can be used to run all projects together, to compare outputs.

Each directory has its own `build.sh` and `run.sh` scripts to build and run the individual application.

## Design
Each huffman implementation should accept input from the terminal with the `-i` flag, and generate the following output:

```bash
user@machine:~$ huffman -i "this is a sample input string. its text is being used to test the huffman coding tree."
input:   [this is a sample input string. its text is being used to test the huffman coding tree.]
encoded: [100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010]
decoded: [this is a sample input string. its text is being used to test the huffman coding tree.]
```

## Implementations
* [c++](c++-huffman/)
* [java](java-huffman/)
* [rust](rust-huffman/)

# Other Resources
* [algorithm](.docs/algorithm.md)
* [todo](.docs/todo.md)

---
