#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$(dirname "$0")")"

mkdir -p build/preprocess
#
# Early-exit if newest touched file among template/, build/preprocess/, and this script is in build/preprocess/
newest_path="$(gfind template build/preprocess "$0" -type f -printf '%T@ %p\n' \
 | gsort -nr | head -n1 | awk '{print $2}')"
[[ "${newest_path:-}" == build/preprocess/* ]] && exit 0

expand() {
  # $1 in, $2 out
  clang++ -std=c++23 -C -E -Wno-pragma-once-outside-header "$1" -o "$2"
}

# Process template/*.cpp files that contain "#ifdef PREPROCESS"
gfind template -type f -name '*.cpp' -print0 \
| while IFS= read -r -d '' file; do
    grep -q '#ifdef PREPROCESS' "$file" || continue

    filename="${file#template/}"
    echo "Processing file: $filename"

    dst_dir="build/preprocess/$(dirname "$filename")"
    mkdir -p "$dst_dir"

    clean_file="build/preprocess/${filename%.cpp}.pre.cpp"
    tmp_src="build/preprocess/$filename"

    cp "$file" "$tmp_src"

    # Temporarily comment out user includes so preprocessor doesn't swallow them
    gsed 's/^[[:space:]]*#include[[:space:]]*"\([^"]*\)"/\/\/***include "\1"/' "$tmp_src" > "$clean_file"

    # Macro expand (keep comments)
    expand "$clean_file" "$clean_file"

    # Drop preprocessor line markers like "# 123 "file.cpp""
    gsed -i '/^#[[:space:]]/d' "$clean_file"

    # Restore includes, add pragma once, remove EXPAND_MACROS
    gsed -i \
      -e 's#//\*\*\*include "\([^"]*\)"#\#include "\1"#' \
      -e '1s;^;#pragma once\n;' \
      -e '/^[[:space:]]*#define[[:space:]]\+EXPAND_MACROS(\b|$)/d' \
      "$clean_file"

    clang-format -i "$clean_file"
    wc -l "$clean_file" | awk '{print $1 " lines\t" $2}'
  done
