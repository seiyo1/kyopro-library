// https://github.com/seiyo1/kyopro-library/blob/main/data_structures/cumsumND.hpp
template<int Dim, typename T>
struct CumsumND {
    vector<int> sizes;  
    vector<T> data;     

    CumsumND(const vector<int>& _sizes) : sizes(_sizes) {
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