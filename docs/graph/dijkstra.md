# Dijkstra

辺の重みが非負のグラフで、単一始点最短路を求めます。

## Usage

```cpp
yz::Dijkstra<long long> graph(n);
graph.add_edge(u, v, cost);

auto dist = graph.shortest_path(start);
```

## メンバー変数

- `static constexpr Cost inf`
    - 到達不能を表す十分大きい値です。

- `vector<vector<Edge>> graph`
    - 隣接リストです。
    - `graph[v]` に頂点 `v` から出る辺を持ちます。

## 構造体

- `Edge`
    - 辺を表す構造体です。

- `int Edge::to`
    - 辺の行き先の頂点です。

- `Cost Edge::cost`
    - 辺の重みです。

## コンストラクタ

- `explicit Dijkstra(int n)`
    - 頂点数 `n` のグラフを作ります。

## 関数

- `void add_edge(int from, int to, Cost cost)`
    - `from` から `to` へ重み `cost` の有向辺を追加します。
    - 無向グラフで使う場合は、逆向きの辺も追加します。

- `vector<Cost> shortest_path(int start) const`
    - 始点 `start` から各頂点への最短距離を返します。
    - 到達できない頂点の距離は `inf` になります。

## Complexity

- `N`: 頂点数
- `M`: 辺数
- Time: `O((N + M) log N)`
- Memory: `O(N + M)`

## Code

```cpp
--8<-- "library/graph/dijkstra.hpp"
```
