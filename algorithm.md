# Algorithm
## Overview
### Building The Tree
1. determine the frequency of each byte that appears in the input data stream
1. for each byte, create a `[symbol:frequency]` pair and add to a list
1. until the list only has a single element remaining, do:
    1. sort the list of `[symbol:frequency]` pairs, first by frequency, and then by symbol
        1. in the simple case, sort by frequencies
        1. if frequencies equal, sort by symbols, if both available
        1. otherwise, sort by the number of elements in each tree; this should allow larger trees to bubble up to the end of the list
    1. remove the first two elements from the list, and merge them
        1. their parent node is an internal node; these have a frequency which is the sum of both child nodes
        1. the two removed elements become the two child nodes
    1. add the new internal node back into the list
    1. repeat

### Encoding
??

### Decoding
??

# Example
This is a trivial example, using the input String `this is a sample input string. its text is being used to test the huffman coding tree.`.

This string results in the following (sorted) frequencies:
```text
[b]=>[1]
[c]=>[1]
[l]=>[1]
[x]=>[1]
[.]=>[2]
[d]=>[2]
[f]=>[2]
[m]=>[2]
[o]=>[2]
[p]=>[2]
[r]=>[2]
[a]=>[3]
[g]=>[3]
[h]=>[3]
[u]=>[3]
[n]=>[5]
[e]=>[8]
[i]=>[8]
[s]=>[8]
[t]=>[11]
[ ]=>[16]
```

---
[Go Back](..)