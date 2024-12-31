#!/usr/bin/env bash
cd "$(dirname "$0")" && cd .. || exit
scripts/preprocess.sh
if ! /Users/konak/Projects/cp/build/cmake-build-release/build/cmake/merger/merger "$@"; then
  rm -f output/merged.cpp
fi