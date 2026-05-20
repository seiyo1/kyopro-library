# Trie

文字列集合を木として管理する最小実装です。

## Usage

```cpp
yz::Trie<> trie;
int node = trie.add("abc");

int prefix_node = trie.find("ab");
int same_word_count = trie.nodes[node].count;
```

## メンバー変数

- `vector<Node> nodes`
    - Trie のノード列です。
    - `nodes[0]` が root です。

## 構造体

- `Node`
    - Trie の各ノードを表す構造体です。

- `array<int, CharSize> Node::next`
    - 各文字で進んだ先のノード番号です。
    - 辺がない場合は `-1` です。

- `int Node::count`
    - このノードで終わる文字列が追加された回数です。

## コンストラクタ

- `Trie()`
    - root だけを持つ空の Trie を作ります。

- `Node()`
    - `next` をすべて `-1` にし、`count` を `0` にします。

## 関数

- `static int char_to_id(char c)`
    - 文字 `c` を `0` 以上 `CharSize` 未満の番号に変換します。
    - デフォルトでは `'a'` が `0`、`'b'` が `1` です。

- `int add(const string &s)`
    - 文字列 `s` を追加します。
    - `s` の終端に対応するノード番号を返します。

- `int find(const string &s) const`
    - 文字列 `s` に対応するノード番号を返します。
    - 見つからない場合は `-1` を返します。

- `int size() const`
    - Trie に含まれるノード数を返します。

## Complexity

- `S`: 追加・検索する文字列の長さ
- Time: `O(S)`
- Memory: `O(ノード数 * 文字種数)`

## Code

```cpp
--8<-- "library/string/trie.hpp"
```
