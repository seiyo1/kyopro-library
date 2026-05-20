#pragma once

#include <array>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

namespace yz {

template <int CharSize = 26, char Base = 'a'>
struct Trie {
  struct Node {
    array<int, CharSize> next;
    int count;  // このノードで終わる文字列が追加された回数

    Node() : count(0) {
      next.fill(-1);
    }
  };

  vector<Node> nodes;

  Trie() : nodes(1) {}

  static int char_to_id(char c) {
    int id = c - Base;
    assert(0 <= id && id < CharSize);
    return id;
  }

  int add(const string &s) {
    int cur = 0;
    for (char c : s) {
      int id = char_to_id(c);
      if (nodes[cur].next[id] == -1) {
        nodes[cur].next[id] = static_cast<int>(nodes.size());
        nodes.emplace_back();
      }
      cur = nodes[cur].next[id];
    }
    nodes[cur].count++;
    return cur;
  }

  int find(const string &s) const {
    int cur = 0;
    for (char c : s) {
      int id = char_to_id(c);
      if (nodes[cur].next[id] == -1) return -1;
      cur = nodes[cur].next[id];
    }
    return cur;
  }

  int size() const {
    return static_cast<int>(nodes.size());
  }
};

}  // namespace yz
