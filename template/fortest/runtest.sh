#!/bin/bash
# コンパイル（すべて fortest フォルダ内に出力）
g++ -O2 -std=c++23 -o fortest/testcase fortest/testcase.cpp
g++ -O2 -std=c++23 -Wall -Wextra -I /home/yz/comp/ac-library -DLOCAL -o fortest/test fortest/test.cpp
g++ -O2 -std=c++23 -o fortest/main main.cpp

# テスト実行ループ
while true; do
    # テストケース生成（標準出力を fortest/input.txt にリダイレクト）
    ./fortest/testcase > fortest/input.txt

    # test.cpp の出力を fortest/out1.txt に保存（正解とみなす）
    ./fortest/test < fortest/input.txt > fortest/out1.txt

    # main.cpp の出力を fortest/out2.txt に保存（検証対象）
    ./fortest/main < fortest/input.txt > fortest/out2.txt

    # 出力を比較。差分があれば diff コマンドは 0 以外の値を返す
    if ! diff -q fortest/out1.txt fortest/out2.txt > /dev/null; then
        echo "不一致のテストケースを発見しました！"
        echo "【入力】"
        cat fortest/input.txt
        echo "【期待される出力（test.cpp の出力）】"
        cat fortest/out1.txt
        echo "【main.cpp の出力】"
        cat fortest/out2.txt
        exit 1
    fi

    # 成功した場合はループを続行
done
