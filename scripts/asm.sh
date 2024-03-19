#!/usr/bin/env bash
cd "$(dirname "$(dirname "$0")")" || exit
#
##$target = "main"
##merger/cmake-build-release/merger
#
##/opt/homebrew/opt/llvm/bin/clang++ -v -std=c++20 -O2 -S -target x86_64-unknown-linux-gnu --sysroot=/Users/konak/Documents/files/archive/ -no-integrated-as "output/merged.cpp" -o "build/main.s" -fno-verbose-asm || exit
#
##clang++ -std=c++20 --sysroot=/Users/konak/Downloads/xwin-0.5.0-aarch64-apple-darwin/.xwin-cache/splat/ -O2 -S -nostdinc -nostdinc++ -target x86_64-unknown-windows-gnu -no-integrated-as main.cpp \
##-isystem ~/Downloads/xwin-0.5.0-aarch64-apple-darwin/.xwin-cache/splat/crt/include/ \
##-isystem ~/Downloads/xwin-0.5.0-aarch64-apple-darwin/.xwin-cache/splat/sdk/include/ucrt/ \
## -fno-verbose-asm -v   -o "build/main.s"
#WINSDK_PATH="/Users/konak/Downloads/xwin-0.5.0-aarch64-apple-darwin/.xwin-cache/splat"
#
#clang-cl -v /FA -c --target=x86-pc-windows-msvc  /winsdkdir "$WINSDK_PATH/sdk" /vctoolsdir "$WINSDK_PATH/crt" /MD main.cpp -o hello.exe
#
##clang++ -S -v -target x86_64-unknown-linux-gnu --sysroot=/Users/konak/Documents/files/archive/ -fuse-ld=lld main.cpp -o build/main.s -O2 -no-integrated-as && ./asm.sh
##gsed -i 's/)"/)\\"/g' build/main.s
##gsed -i '/\s#/ s/#.*//' build/main.s
##gsed -i 's/throw_bad_array_new_length/throw_bad_array_now_length/g' build/main.s
#mv main.asm build/main.s
#
#i686-w64-mingw32-g++ main.cpp -S -o build/main.s
i686-w64-mingw32-g++ -v main.cpp -S -o build/main.s -pie -march=skylake -m32 -fasm-blocks

# shellcheck disable=SC2016
gsed -e '1i\__asm__(R"asm_marker('  -e '$a\)asm_marker");' build/main.s > build/asm.cpp
ls -lh build/asm.cpp
