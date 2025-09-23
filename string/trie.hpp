struct Node {
  int id;
  array<int, 26> nxt;
  Node(int id) {
    this->id = id;
    nxt.fill(-1);
  };
};

vector<Node> tr;
tr.push_back(Node(0));

auto insert = [&](string &s) -> void {
    int cur = 0;
    for (auto &&c : s) {
      if (tr[cur].nxt[c - 'a'] == -1) {
        tr[cur].nxt[c - 'a'] = (int)tr.size();
        tr.push_back(Node((int)tr.size()));
      }
      cur = tr[cur].nxt[c - 'a'];
    };