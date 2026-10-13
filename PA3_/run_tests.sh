#!/bin/bash
# PA3 test runner.
# Usage: ./run_tests.sh [source.c] [test_folder]
#   ./run_tests.sh               tests main.c against ./in*.txt
#   ./run_tests.sh main1.c       tests main1.c
#   ./run_tests.sh main1.c edge  tests main1.c against edge/in*.txt
# Each inN.txt is run through the program and compared with outN.txt.
# Your program's output goes to results/, so outN.txt is never overwritten.

SRC=${1:-main.c}
DIR=${2:-.}
BIN=./pa3_test
RES=results
mkdir -p "$RES"

echo "== Compiling $SRC"
if ! gcc -Wall -Wextra -std=c99 -g -o "$BIN" "$SRC"; then
    echo "COMPILE FAILED: fix the errors above first."
    exit 1
fi

HAS_VG=0
if command -v valgrind > /dev/null; then HAS_VG=1; else
    echo "(valgrind not installed: leak checks skipped. Install: sudo apt-get update && sudo apt-get install -y valgrind)"
fi

pass=0; fail=0; total=0
for in_file in "$DIR"/in*.txt; do
    [ -e "$in_file" ] || { echo "No in*.txt files in $DIR"; exit 1; }
    n=$(basename "$in_file" .txt); n=${n#in}
    exp="$DIR/out$n.txt"
    if [ "$DIR" = "." ]; then tag=$n; else tag=$(basename "$DIR")_$n; fi
    got="$RES/my_$tag.txt"
    if [ ! -f "$exp" ]; then echo "-- in$n.txt: skipped (no out$n.txt)"; continue; fi
    total=$((total+1))

    timeout 10 "$BIN" < "$in_file" > "$got"
    code=$?

    # strict = byte-for-byte. lenient ignores \r and trailing spaces, to tell
    # a real logic difference apart from an invisible whitespace difference.
    if diff -q "$got" "$exp" > /dev/null; then out_res="PASS"
    elif diff -q --strip-trailing-cr -Z "$got" "$exp" > /dev/null; then out_res="WHITESPACE-ONLY"
    else out_res="FAIL"; fi
    [ $code -eq 124 ] && out_res="TIMEOUT (infinite loop?)"

    mem_res="-"
    if [ $HAS_VG -eq 1 ]; then
        vg="$RES/valgrind_$tag.txt"
        valgrind --leak-check=full "$BIN" < "$in_file" > /dev/null 2> "$vg"
        if grep -q "ERROR SUMMARY: 0 errors" "$vg" && grep -q "in use at exit: 0 bytes" "$vg"; then
            mem_res="clean"
        else
            mem_res="PROBLEM (see $vg)"
        fi
    fi

    echo "-- in$n.txt: output $out_res | memory $mem_res"
    if [ "$out_res" = "PASS" ] && [ "$mem_res" != "PROBLEM (see $vg)" ]; then
        pass=$((pass+1))
    else
        fail=$((fail+1))
        if [ "$out_res" = "WHITESPACE-ONLY" ]; then
            echo "   Same text; only line endings or trailing spaces differ."
            if grep -q $'\r' "$exp"; then echo "   note: out$n.txt has Windows line endings (\\r). Fix the file with: sed -i 's/\\r\$//' $exp"; fi
        elif [ "$out_res" != "PASS" ]; then
            echo "   < expected (out$n.txt)   > yours ($got)"
            diff "$exp" "$got" | head -20 | sed 's/^/   /'
            if grep -q $'\r' "$exp"; then echo "   note: out$n.txt has Windows line endings (\\r)."; fi
            if grep -q $'\xe2\x80\x99' "$exp"; then echo "   note: out$n.txt contains curly apostrophes (’), likely copied from the PDF. Your straight ' is correct."; fi
            echo "   tip: cat -A $got | head   shows line ends as \$ and odd bytes"
        fi
    fi
done

echo "== $pass/$total passed"
[ $fail -eq 0 ]
