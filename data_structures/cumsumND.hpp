// https://github.com/seiyo1/kyopro-library/blob/main/data_structures/cumsumND.hpp
/*
多次元累積和
add({x,y,z},val);　座標(x,y,z)(0-indexed)にvalを加算
build();    累積和を構築
query({lx,ly,lz},{rx,ry,rz}); 0-indexedの[l,r)の総和を取得

例:
  cumsumND<2, int> cs({H, W}); // 2次元H×Wの累積和
  cs.add({y, x}, val);              // (y, x) に val を加算
  cs.build();                       // 累積和を構築
  auto sum = cs.query({y1, x1}, {y2, x2}); // 矩形[y1,y2)×[x1,x2) の和を取得
*/
template<int Dim, typename T>
struct cumsumND {
    vector<int> sizes;  
    vector<T> data;     

    cumsumND(const vector<int>& _sizes) : sizes(_sizes) {
        assert(sizes.size() == Dim);
        int total_size = 1;
        for (int sz : sizes) total_size *= (sz + 1); // 1-indexed化
        data.assign(total_size, 0);
    }

    int index(const vector<int>& coords) const {
        int idx = 0, stride = 1;
        for (int d = Dim-1; d >= 0; --d) {
            idx += coords[d] * stride;
            stride *= sizes[d]+1;
        }
        return idx;
    }

    void add(const vector<int>& coords, T val) {
        vector<int> shifted = coords;
        for (int& c : shifted) ++c; 
        data[index(shifted)] += val;
    }

    void build() {
        vector<int> coords(Dim), limits(Dim);
        for (int i = 0; i < Dim; ++i) limits[i] = sizes[i]+1;
        for (int d = 0; d < Dim; ++d) {
            function<void(int)> dfs = [&](int depth) {
                if (depth == Dim) {
                    if (coords[d] >= 1)
                        data[index(coords)] += data[index([&] {
                            auto tmp = coords;
                            tmp[d]--;
                            return tmp;
                        }())];
                    return;
                }
                for (coords[depth] = 0; coords[depth] < limits[depth]; ++coords[depth])
                    dfs(depth+1);
            };
            dfs(0);
        }
    }

    T query(const vector<int>& starts, const vector<int>& ends) const {
        assert(starts.size() == Dim && ends.size() == Dim);
        T res = 0;
        for (int mask = 0; mask < (1 << Dim); ++mask) {
            vector<int> coords(Dim);
            int parity = 1;
            for (int d = 0; d < Dim; ++d) {
                if (mask & (1 << d)) {
                    coords[d] = starts[d];
                    parity *= -1;
                } else {
                    coords[d] = ends[d];
                }
            }
            res += parity * data[index(coords)];
        }
        return res;
    }
};