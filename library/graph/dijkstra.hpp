#pragma once

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

namespace yz {

template <class Cost = long long>
struct Dijkstra {
  struct Edge {
    int to;
    Cost cost;
  };

  static constexpr Cost inf = numeric_limits<Cost>::max() / 4;
  vector<vector<Edge>> graph;

  explicit Dijkstra(int n) : graph(n) {}

  void add_edge(int from, int to, Cost cost) {
    graph[from].push_back({to, cost});
  }

  vector<Cost> shortest_path(int start) const {
    vector<Cost> dist(graph.size(), inf);
    priority_queue<pair<Cost, int>, vector<pair<Cost, int>>,
                        greater<pair<Cost, int>>>
        que;

    dist[start] = 0;
    que.emplace(0, start);

    while (!que.empty()) {
      auto [d, v] = que.top();
      que.pop();
      if (d != dist[v]) continue;

      for (const Edge &edge : graph[v]) {
        Cost nd = d + edge.cost;
        if (nd >= dist[edge.to]) continue;
        dist[edge.to] = nd;
        que.emplace(nd, edge.to);
      }
    }

    return dist;
  }
};

}  // namespace yz
