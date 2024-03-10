#!/usr/bin/env bash
cd "$(dirname "$(dirname "$0")")" || exit

merger/merger.sh
clang++ -std=c++20 output/merged.cpp -o build/merged && build/merged < input.txt
