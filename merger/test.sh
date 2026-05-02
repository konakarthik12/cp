#!/usr/bin/env bash
cd "$(dirname "$0")" && cd .. || exit
merger/merge.sh
g++-15 -std=c++23 output/merged.cpp -O3 -o build/merged "$@" && build/merged < input.txt
