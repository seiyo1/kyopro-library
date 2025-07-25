// https://github.com/seiyo1/kyopro-library/blob/main/data_structures/rangeset.hpp
template <typename T>
struct rangeset {
  set<pair<T, T>> s;
  T iinf = numeric_limits<T>::max();
  rangeset() {}
  void insert(T L, T R) {
    auto itL = s.upper_bound({L, iinf});
    auto itR = s.upper_bound({R, iinf});
    if (itL != s.begin() && (--itL)->second < L) ++itL;
    if (itL != itR) {
      L = min(L, itL->first);
      R = max(R, prev(itR)->second);
      s.erase(itL, itR);
    }
    s.insert({L, R});
  }

  void erase(T L, T R) {
    T LL = -1, LR = -1, RL = -1, RR = -1;
    auto itL = s.upper_bound({L, iinf});
    auto itR = s.upper_bound({R, iinf});
    if (itL != s.begin() && (--itL)->second <= L) ++itL;
    if (itL != itR) {
      if (itL->first < L) {
        LL = itL->first;
        LR = L;
      }
      if (prev(itR)->second > R) {
        RL = R;
        RR = prev(itR)->second;
      }
      s.erase(itL, itR);
    }
    if (LL != -1) s.insert({LL, LR});
    if (RR != -1) s.insert({RL, RR});
  }
  // [1,2) [2,3)はNo.
  bool hasOverlap(T L, T R) {
    auto it = s.lower_bound({R, numeric_limits<T>::lowest()});
    if (it == s.begin()) return false;
    --it;
    return it->second > L;
  }

  unsigned int size() { return s.size(); }
};