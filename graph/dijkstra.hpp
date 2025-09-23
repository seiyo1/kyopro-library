vector<ll> dijkstra(const vector<vector<pair<ll, ll>>> &g, ll start) {
  int n = (int)g.size();
  vector<ll> dist(n, LLONG_MAX / 4);
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
      pq;
  dist[start] = 0;
  pq.emplace(0, start);
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d > dist[v]) continue;
    for (auto &e : g[v]) {
      ll to = e.first;
      ll cost = e.second;
      ll nd = d + cost;
      if (nd < dist[to]) {
        dist[to] = nd;
        pq.emplace(nd, to);
      }
    }
  }
  return dist;
}