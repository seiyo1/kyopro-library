// https://github.com/seiyo1/kyopro-library/blob/main/graph/dijkstra.hpp
template <typename T>
vector<T> dijkstra(const vector < vector<pair<int, T>> & g, int start) {
  int n = g.size();
  const T INF = numeric_limits<T>::max();
  vector<T> dist(n, INF);
  using P = pair<T, int>;
  priority_queue<P, vector<P>, greater<P>> pq;

  dist[start] = 0;
  pq.emplace(0, start);
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d > dist[v]) continue;
    for (auto& [to, cost] : g[v]) {
      T nd = d + cost;
      if (nd < dist[to]) {
        dist[to] = nd;
        pq.emplace(nd, to);
      }
    }
  }
  return dist;
}
