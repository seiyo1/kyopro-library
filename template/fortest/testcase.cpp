#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <set>

// using namespace std; を先頭で宣言
using namespace std;

// 乱数生成器をまとめた構造体
struct Random {
    mt19937 mt;

    // コンストラクタ: シード値を指定しない場合は現在時刻をシードにする
    Random() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}

    // コンストラクタ: シード値を指定する場合
    Random(unsigned int seed) : mt(seed) {}

    // [min, max] の範囲の整数乱数を生成
    long long get_int(long long min_val, long long max_val) {
        uniform_int_distribution<long long> dist(min_val, max_val);
        return dist(mt);
    }

    // [min, max) の範囲の実数乱数を生成
    double get_double(double min_val, double max_val) {
        uniform_real_distribution<double> dist(min_val, max_val);
        return dist(mt);
    }

    // 長さ len のランダムなベクターを生成
    // 各要素は [min_val, max_val] の範囲
    vector<long long> get_vec(int len, long long min_val, long long max_val) {
        vector<long long> vec(len);
        for (int i = 0; i < len; ++i) {
            vec[i] = get_int(min_val, max_val);
        }
        return vec;
    }

    // 長さ len のランダムな文字列を生成
    // 使用する文字は chars からランダムに選ばれる
    string get_str(int len, const string& chars = "abcdefghijklmnopqrstuvwxyz") {
        string str(len, ' ');
        for (int i = 0; i < len; ++i) {
            str[i] = chars[get_int(0, chars.length() - 1)];
        }
        return str;
    }

    // 頂点数 V のランダムな木を生成 (辺のリストを返す)
    // 頂点番号は 1-indexed
    vector<pair<int, int>> get_tree(int V) {
        if (V <= 1) return {};
        
        // Prufer sequence を利用してランダムな木を生成
        vector<int> prufer(V - 2);
        for(int i = 0; i < V - 2; ++i) {
            prufer[i] = get_int(1, V);
        }
        
        vector<int> degree(V + 1, 1);
        for (int node : prufer) {
            degree[node]++;
        }

        set<int> leaves;
        for (int i = 1; i <= V; i++) {
            if (degree[i] == 1) {
                leaves.insert(i);
            }
        }
        
        vector<pair<int, int>> edges;
        for (int node : prufer) {
            int leaf = *leaves.begin();
            leaves.erase(leaves.begin());
            
            edges.emplace_back(leaf, node);
            
            degree[leaf]--;
            degree[node]--;
            if (degree[node] == 1) {
                leaves.insert(node);
            }
        }
        edges.emplace_back(*leaves.begin(), *leaves.rbegin());
        
        return edges;
    }

    // Yes/No を確率 p でYesとして出力
    bool yes(double p = 0.5) {
        return get_double(0.0, 1.0) < p;
    }
};

// --- 以下、使用例 ---

// 配列をスペース区切りで出力するヘルパー関数
template<typename T>
void print_vector(const vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
// 競技プログラミングで一般的な高速化設定
ios_base::sync_with_stdio(false);
cin.tie(NULL);

// シード値を指定して初期化（デバッグ時に同じテストケースを再現できる）
// Random rnd(12345); 
// シード値を指定しない場合（実行ごとに異なるテストケースが生成される）
Random rnd;
int n=rnd.get_int(1,100);
string t=rnd.get_str(n,"abc");


return 0;
}