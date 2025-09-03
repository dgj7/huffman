# huffman
## Purpose
huffman coding trees, in various languages.  intended to be a personal programming challenge for new languages learned.

## Implementations
* ![c++](https://github.com/dgj7/huffman/actions/workflows/cpp.yml/badge.svg) (_[code](c++/)_) _build requires **cmake**, **g++**, and **build-essential**_
* ![rust](https://github.com/dgj7/huffman/actions/workflows/rust.yml/badge.svg) (_[code](rust/)_) _build requires **cargo**_
* ![go](https://github.com/dgj7/huffman/actions/workflows/go.yml/badge.svg) (_[code](go/)_) _build requires **go**_
* ![java](https://github.com/dgj7/huffman/actions/workflows/java.yml/badge.svg) [code](java/) _build requires **maven** and **jdk 1.7**_
* ![c](https://github.com/dgj7/huffman/actions/workflows/c.yml/badge.svg) (_[code](c/)_) _build requires **cmake**, **gcc**, and **build-essential**_

## Usage
### Build
There is a `build-and-run-all.sh` script in the root directory that can be used to run all projects together, to compare outputs.

Each directory has its own `build.sh` and `run.sh` scripts to build and run the individual applications.

### Run
Each huffman implementation should accept input from the terminal with the `-i` flag, and generate the following output:

```bash
user@machine:~$ huffman -i "this is a sample input string. its text is being used to test the huffman coding tree."
input:   [this is a sample input string. its text is being used to test the huffman coding tree.]
encoded: [100101110000011110000011111010111100110101010010101110100011011110000111010111100010011100110001100000011110110110010111000100001111100110110100110011100000111101101011010000111101101111100000111011100111111000101011110011010011001111001011111011111011111000010000100001001101010111111011011010101100110000111101101111000110011011101110010]
decoded: [this is a sample input string. its text is being used to test the huffman coding tree.]
```

# Other Resources
* [algorithm](.docs/algorithm.md) used for generating output
* [analysis](.docs/analysis.md) comparing all program outputs
* [todo](.docs/todo.md) items remaining

---
