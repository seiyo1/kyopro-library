#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define DEBUG_COLOR "\033[36m"
    #define RESET_COLOR "\033[0m"

    // ─── 内部実装：型ごとに print ──────────────────────────
    namespace dbg_detail {
        // 基本：ostream に直接流せる型
        template<class T>
        concept Streamable = requires(ostream& os, const T& v) { os << v; };

        // 1. Streamable (string もここで処理)
        template<Streamable T>
        void print(const T& v) { cout << v; }

        // 2. pair
        template<class U, class V>
        void print(const pair<U,V>& p) {
            cout << '('; print(p.first); cout << ", "; print(p.second); cout << ')';
        }

        // 3. tuple
        template<size_t I = 0, class... Ts>
        void print_tuple(const tuple<Ts...>& t) {
            if constexpr(I < sizeof...(Ts)) {
                if constexpr(I) cout << ", ";
                print(get<I>(t));
                print_tuple<I+1>(t);
            }
        }
        template<class... Ts>
        void print(const tuple<Ts...>& t) {
            cout << '('; print_tuple(t); cout << ')';
        }

        // 4. 反復可能（string は除外）
        template<class C>
        concept Iterable =
            !is_same_v<C,string> &&
            requires (const C& c) { c.begin(); c.end(); };

        template<Iterable C>
        void print(const C& c) {
            cout << '[';
            bool first = true;
            for (const auto& x : c) {
                if (!first) cout << ' ';
                first = false;
                print(x);
            }
            cout << ']';
        }
    } // namespace dbg_detail

    // ─── 公開インターフェース ──────────────────────────────
    template<class... Args>
    void de(const Args&... args) {
        cout << DEBUG_COLOR;
        ((dbg_detail::print(args), cout << ' '), ...);
        cout << RESET_COLOR << '\n';
    }

#else   // ─── LOCAL が無いときは無効化 ────────────────────────
    template<class... Args>
    void de(const Args&...) {}
#endif

#endif // DEBUG_HPP
