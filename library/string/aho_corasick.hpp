#pragma once

#include <array>
#include <cassert>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace yz {

template <int CharSize = 26, char Base = 'a'>
struct AhoCorasick {
  struct Node {
    array<int, CharSize> next;
    int fail;
    vector<int> accept;

    Node() : fail(0) {
      next.fill(-1);
    }
  };

  vector<Node> nodes;
  int word_count;
  bool built;

  AhoCorasick() : nodes(1), word_count(0), built(false) {}

  static int char_to_id(char c) {
    int id = c - Base;
    assert(0 <= id && id < CharSize);
    return id;
  }

  int add(const string &s) {
    return add(s, word_count++);
  }

  int add(const string &s, int word_id) {
    assert(!built);
    int cur = 0;
    for (char c : s) {
      int id = char_to_id(c);
      if (nodes[cur].next[id] == -1) {
        nodes[cur].next[id] = static_cast<int>(nodes.size());
        nodes.emplace_back();
      }
      cur = nodes[cur].next[id];
    }
    nodes[cur].accept.push_back(word_id);
    if (word_id >= word_count) word_count = word_id + 1;
    return cur;
  }

  void build() {
    if (built) return;

    queue<int> que;

    for (int c = 0; c < CharSize; c++) {
      int to = nodes[0].next[c];
      if (to == -1) {
        nodes[0].next[c] = 0;
      } else {
        nodes[to].fail = 0;
        que.push(to);
      }
    }

    while (!que.empty()) {
      int v = que.front();
      que.pop();

      for (int c = 0; c < CharSize; c++) {
        int to = nodes[v].next[c];
        if (to == -1) {
          nodes[v].next[c] = nodes[nodes[v].fail].next[c];
          continue;
        }

        nodes[to].fail = nodes[nodes[v].fail].next[c];
        const vector<int> &suffix_accept = nodes[nodes[to].fail].accept;
        nodes[to].accept.insert(nodes[to].accept.end(), suffix_accept.begin(),
                                suffix_accept.end());
        que.push(to);
      }
    }

    built = true;
  }

  int move(int v, char c) const {
    assert(built);
    return nodes[v].next[char_to_id(c)];
  }

  vector<pair<int, int>> match(const string &text) const {
    assert(built);
    vector<pair<int, int>> res;
    int cur = 0;
    for (int i = 0; i < static_cast<int>(text.size()); i++) {
      cur = move(cur, text[i]);
      for (int word_id : nodes[cur].accept) {
        res.emplace_back(i, word_id);
      }
    }
    return res;
  }
};

}  // namespace yz
