#!/usr/bin/env bash
cd "$(dirname "$0")" && cd .. || exit
merger/merge.sh
bat --paging=never output/merged.cpp
