#!/usr/bin/env bash
cd "$(dirname "$(dirname "$0")")" || exit
scripts/preprocess.sh
if ! merger/cmake-build-release/merger; then
  rm output/merged.cpp
fi