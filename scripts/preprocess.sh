#!/usr/bin/env bash
cd "$(dirname "$(dirname "$0")")" || exit

if gfind template build/preprocess/ "$0" -type f -printf '%T@ %p\n'  | sort -n -r | head -n 1 | grep -q build/preprocess; then
  exit
fi

pattern="template/**.cpp"
function expand () {
     clang++ -std=c++23 -C -E -Wno-pragma-once-outside-header "$1" -o "$2" || exit

}
# Iterate over each file matching the pattern
for file in $pattern; do
    filename="${file#template/}"

    if ! grep -q "#ifdef PREPROCESS" "$file"; then
      continue
    fi

    echo "Processing file: $filename"

    clean_file="build/preprocess/${filename%.cpp}.pre.cpp"

    cp "$file" "build/preprocess/$filename"

    gsed 's/^\s*#include\s*"\(.*\)"/\/\/***include "\1"/' "build/preprocess/$filename" > "$clean_file"

    expand "$clean_file" "$clean_file"

    gsed -i '/^#\s/d' "$clean_file"

    wc -l "$clean_file"

    gsed -i -e 's/\/\/\*\*\*include "\(.*\)"/#include "\1"/' -e "1s;^;#pragma once\n;" -e '/#define EXPAND_MACROS/d' "$clean_file"
    clang-format -i "$clean_file"
done