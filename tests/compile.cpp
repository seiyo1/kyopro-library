#include <cassert>

#include "graph/dijkstra.hpp"

int main() {
  yz::Dijkstra<long long> graph(3);
  graph.add_edge(0, 1, 2);
  graph.add_edge(1, 2, 3);
  graph.add_edge(0, 2, 10);
  auto dist = graph.shortest_path(0);
  assert(dist[2] == 5);
}
