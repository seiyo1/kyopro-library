# Trie

文字列集合を木として管理する最小実装です。

## Complexity

- `S`: 追加・検索する文字列の長さ
- Time: `O(S)`
- Memory: `O(ノード数 * 文字種数)`

## Code

```cpp
--8<-- "library/string/trie.hpp"
```

## Usage

```cpp
yz::Trie<> trie;
int node = trie.add("abc");

int prefix_node = trie.find("ab");
int same_word_count = trie.nodes[node].count;
```
