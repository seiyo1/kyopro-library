// O(n)
// "$"を含んだ伸ばせる長さ+1を返す
// 回文の長さは rad[i]-1
vector<int> manacher(string &s) {
  string t = "$";
  for (auto &&c : s) {
    t += c;
    t += "$";
  }
  int n = (int)t.size();
  int mid = 0, r = 0;
  vector<int> rad(n);
  while (mid < n) {
    //どこまで伸ばせるか
    while (mid - r >= 0 && mid + r < n && t[mid - r] == t[mid + r]) r++;
    rad[mid] = r;
    //鏡写し
    int k = 1;
    while (mid - k >= 0 && mid + k < n && k + rad[mid - k] < r) {
      rad[mid + k] = rad[mid - k];
      k++;
    }
    //写した分をスキップ
    mid += k;
    r -= k;
  }
  return rad;
}