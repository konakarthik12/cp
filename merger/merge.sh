#!/usr/bin/env bash
cd "$(dirname "$0")" && cd .. || exit
scripts/preprocess.sh
if ! merger/cmake-build-release/merger "$@"; then
  rm -f output/merged.cpp
fi