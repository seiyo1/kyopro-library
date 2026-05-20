# Aho-Corasick

複数の文字列をまとめて検索します。

## Complexity

- `P`: 追加した文字列の長さの合計
- `T`: 検索する文字列の長さ
- `Z`: 見つかった個数
- Build: `O(P * 文字種数 + 出力リストの合計長)`
- Match: `O(T + Z)`
- Memory: `O(ノード数 * 文字種数 + 出力リストの合計長)`

## Code

```cpp
--8<-- "library/string/aho_corasick.hpp"
```

## Usage

```cpp
yz::AhoCorasick<> ac;
ac.add("he", 0);
ac.add("she", 1);
ac.add("hers", 2);
ac.build();

auto matches = ac.match("ushers");
```

`match` は `(終端位置, 文字列ID)` の列を返します。

## Build の例

`he`, `she`, `his`, `hers` を追加した例です。
まず Trie の形は次の通りです（辺のラベルは追加する文字）。

```mermaid
flowchart TB
  R(("root"))
  H(("h"))
  HE(("he<br/>受理: he"))
  HER(("her"))
  HERS(("hers<br/>受理: hers"))
  HI(("hi"))
  HIS(("his<br/>受理: his"))
  S(("s"))
  SH(("sh"))
  SHE(("she<br/>受理: she, he"))

  R -- "h" --> H
  H -- "e" --> HE
  HE -- "r" --> HER
  HER -- "s" --> HERS
  H -- "i" --> HI
  HI -- "s" --> HIS
  R -- "s" --> S
  S -- "h" --> SH
  SH -- "e" --> SHE

  classDef root fill:#f8fafc,stroke:#334155,stroke-width:2px,color:#0f172a;
  classDef normal fill:#dbeafe,stroke:#2563eb,stroke-width:2px,color:#172554;
  classDef accept fill:#dcfce7,stroke:#16a34a,stroke-width:2px,color:#052e16;

  class R root;
  class H,HER,HI,S,SH normal;
  class HE,HERS,HIS,SHE accept;

  linkStyle 0,1,2,3,4,5,6,7,8 stroke:#2563eb,stroke-width:2px;
```

`build()` では BFS で浅いノードから順に `fail` を決めます。
たとえば `sh` の `fail` は `h` なので、`she` の `fail` は
`h` から `e` で進んだ `he` になります。

点線の矢印で `fail` をすべて結ぶと、次のような木になります。
どのノードからたどっても、最後は必ず `root` に着きます。

```mermaid
flowchart BT
  R(("root"))
  H(("h"))
  HE(("he"))
  S(("s"))
  HI(("hi"))
  HER(("her"))
  SH(("sh"))
  SHE(("she"))
  HIS(("his"))
  HERS(("hers"))

  H -.-> R
  HE -.-> R
  S -.-> R
  HI -.-> R
  HER -.-> R
  SH -.-> H
  SHE -.-> HE
  HIS -.-> S
  HERS -.-> S

  classDef root fill:#f8fafc,stroke:#334155,stroke-width:2px,color:#0f172a;
  classDef normal fill:#dbeafe,stroke:#2563eb,stroke-width:2px,color:#172554;
  classDef accept fill:#dcfce7,stroke:#16a34a,stroke-width:2px,color:#052e16;

  class R root;
  class H,S,HI,HER,SH normal;
  class HE,HIS,HERS,SHE accept;

  linkStyle 0,1,2,3,4,5,6,7,8 stroke:#ef4444,stroke-width:2px,stroke-dasharray:5 5;
```

```cpp
nodes[to].fail = nodes[nodes[v].fail].next[c];
```

`to == -1` のときは、`fail` 先の遷移で `next` を埋めます。
これで `match()` 中に毎回 `fail` をたどらず、1 文字で必ず次の状態へ進めます。
下の表は、補完される `next` の代表例です。
状態 `v` が文字 `c` の辺を持たないとき、`next[v][c]` は
`fail` 先（中央列）の `next` をそのまま引き継ぎます。

| 遷移元の状態 | 入力文字 | たどる `fail` 先 | 補完される `next` |
| --- | --- | --- | --- |
| `sh` | `i` | `h` | `hi` |
| `she` | `r` | `he` | `her` |
| `his` | `h` | `s` | `sh` |
| `hers` | `h` | `s` | `sh` |
| `he` | `h` | `root` | `h` |
| `her` | `h` | `root` | `h` |
| `s` | `e` | `root` | `root` |
