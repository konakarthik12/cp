#!/usr/bin/env bash

mkdir -p /opt/homebrew/opt/llvm/include/c++/v1/bits/
cp stdc++.h /opt/homebrew/opt/llvm/include/c++/v1/bits/
clang++ -x c++-header -std=c++23 stdc++.h -O3 -o /opt/homebrew/opt/llvm/include/c++/v1/bits/stdc++.h.pch
clang++ -x c++-header -std=c++23 stdc++.h  -fsanitize=address -o /opt/homebrew/opt/llvm/include/c++/v1/bits/stdc++.h.pch.deb

