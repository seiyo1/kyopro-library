# kyopro-library

競技プログラミング用ライブラリです。

ドキュメントは MkDocs Material で管理し、説明文は `docs/`、実装は
`library/` に分けています。各ページでは `library/*.hpp` を snippet として
埋め込むため、コードを Markdown にコピペせずに公開できます。

## 構成

```text
docs/       # 説明・使い方・計算量
library/    # 提出用 C++ ヘッダ
mkdocs.yml  # GitHub Pages 用ドキュメント設定
```

## 使い方

開発中は ACL と同じように、必要なヘッダを include して使います。

```cpp
#include "library/graph/dijkstra.hpp"

yz::Dijkstra<long long> graph(n);
```

提出時は expander で include 先を展開し、1 つの `.cpp` にまとめます。

```sh
python3 tools/expand.py main.cpp -o submit.cpp
```

## ローカル確認

```sh
python3 -m venv .venv
.venv/bin/python -m pip install -r requirements.txt
.venv/bin/mkdocs serve
```

## 公開

`main` に push すると GitHub Actions が `mkdocs build --strict` を実行し、
生成された静的サイトを GitHub Pages にデプロイします。
