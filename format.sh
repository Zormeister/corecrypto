find . -iname '*.c' -not -path "*/include/*"  | clang-format --style=file -i --files=/dev/stdin
