#include <cassert>

#include "graph/dijkstra.hpp"
#include "math/matrix.hpp"
#include "string/aho_corasick.hpp"
#include "string/trie.hpp"

int main() {
  yz::Dijkstra<long long> graph(3);
  graph.add_edge(0, 1, 2);
  graph.add_edge(1, 2, 3);
  graph.add_edge(0, 2, 10);
  auto dist = graph.shortest_path(0);
  assert(dist[2] == 5);

  yz::Trie<> trie;
  int abc = trie.add("abc");
  int abd = trie.add("abd");
  int ab = trie.find("ab");
  int missing = trie.find("ac");
  assert(abc != abd);
  assert(ab != -1);
  assert(missing == -1);
  assert(trie.nodes[abc].count == 1);
  assert(trie.nodes[abd].count == 1);
  assert(trie.nodes[ab].count == 0);

  yz::AhoCorasick<> ac;
  ac.add("he", 0);
  ac.add("she", 1);
  ac.add("his", 2);
  ac.add("hers", 3);
  ac.build();
  auto matches = ac.match("ushers");
  bool saw_he = false;
  bool saw_she = false;
  bool saw_hers = false;
  for (auto [end, id] : matches) {
    if (end == 3 && id == 0) saw_he = true;
    if (end == 3 && id == 1) saw_she = true;
    if (end == 5 && id == 3) saw_hers = true;
  }
  assert(saw_he);
  assert(saw_she);
  assert(saw_hers);

  yz::Matrix<long long> mat(2, 2);
  mat[0][0] = 1;
  mat[0][1] = 1;
  mat[1][0] = 1;
  mat[1][1] = 0;
  auto squared = mat * mat;
  assert(squared[0][0] == 2);
  assert(squared[0][1] == 1);
  assert(squared[1][0] == 1);
  assert(squared[1][1] == 1);
  auto powered = mat ^ 5;
  assert(powered[0][0] == 8);
  assert(powered[0][1] == 5);
  assert(powered[1][0] == 5);
  assert(powered[1][1] == 3);
}
