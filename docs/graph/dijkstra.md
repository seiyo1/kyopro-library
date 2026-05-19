# Dijkstra

辺の重みが非負のグラフで、単一始点最短路を求めます。

## Complexity

- `N`: 頂点数
- `M`: 辺数
- Time: `O((N + M) log N)`
- Memory: `O(N + M)`

## Code

```cpp
--8<-- "library/graph/dijkstra.hpp"
```

## Usage

```cpp
yz::Dijkstra<long long> graph(n);
graph.add_edge(u, v, cost);

auto dist = graph.shortest_path(start);
```
