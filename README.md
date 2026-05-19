# kyopro-library

競技プログラミング用ライブラリです。

## 使い方

```cpp
#include "graph/dijkstra.hpp"

yz::Dijkstra<long long> graph(n);
```

コンパイル時は `library/` に include path を通します。

```sh
g++ -std=c++17 -I library a.cpp
```

提出時は expander で include 先を展開し、1 つの `.cpp` にまとめます。

```sh
python3 tools/expand.py a.cpp -o submit.cpp
```
