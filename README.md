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
encoded: [001011]
decoded: [this is a sample input string. its text is being used to test the huffman coding tree.]
```

## Implementations
* [c++](c++-huffman/)
* [java](java-huffman/)
* [rust](rust-huffman/)

# Other Resources
* [algorithm](algorithm.md)

---
