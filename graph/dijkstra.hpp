// https://github.com/seiyo1/kyopro-library/blob/main/graph/dijkstra.hpp
vector<ll> dijkstra(const vector<vector<P>> &g, ll start) {
  int n = (int)g.size();
  vector<ll> dist(n, INF);
  priority_queue<P, vector<P>, greater<P>> pq;
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