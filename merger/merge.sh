#!/usr/bin/env bash
cd "$(dirname "$0")" && cd .. || exit
rm -f output/merged.cpp
scripts/preprocess.sh
/Users/konak/Projects/cp/release/build/cmake/merger/merger
