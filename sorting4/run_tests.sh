#!/usr/bin/env bash
# run_tests.sh — compile, run the provided in/out pairs, Valgrind each one,
# then random stress tests checked against an independent Python sort,
# then an AddressSanitizer/UBSan build over everything.
#
# Usage:  bash run_tests.sh [source.c]        (default: monster_rankings.c)
# Run it from the folder that holds inN.txt / outN.txt.

SRC="${1:-monster_rankings.c}"
BIN="./mr_test"
PASS=0; FAIL=0

say()  { printf '\n\033[1;35m== %s ==\033[0m\n' "$*"; }
ok()   { printf '  \033[32mPASS\033[0m %s\n' "$*"; PASS=$((PASS+1)); }
bad()  { printf '  \033[31mFAIL\033[0m %s\n' "$*"; FAIL=$((FAIL+1)); }

# ---------------------------------------------------------------- 1. compile
say "1. Compile with warnings on"
if gcc -Wall -Wextra -std=c99 -g "$SRC" -o "$BIN" 2> compile.log; then
    if [ -s compile.log ]; then bad "compiled, but with warnings (see compile.log):"; sed 's/^/      /' compile.log; else ok "zero warnings"; fi
else
    bad "did not compile:"; sed 's/^/      /' compile.log; exit 1
fi

# ---------------------------------------------------------------- 2. provided tests
say "2. Provided test cases (inN.txt vs outN.txt)"
for inp in in*.txt; do
    [ -e "$inp" ] || { echo "  no inN.txt files found"; break; }
    n="${inp#in}"; n="${n%.txt}"; exp="out${n}.txt"
    [ -e "$exp" ] || { echo "  $inp has no $exp, skipped"; continue; }
    timeout 10 "$BIN" < "$inp" > "got${n}.txt" 2>/dev/null
    rc=$?
    if [ $rc -eq 124 ]; then bad "$inp: TIMEOUT (over 10 s)"; continue; fi
    if diff -q "got${n}.txt" "$exp" > /dev/null; then
        ok "$inp"
    else
        bad "$inp  (first differences below; full diff: diff got${n}.txt $exp)"
        diff "got${n}.txt" "$exp" | head -8 | sed 's/^/      /'
    fi
done

# ---------------------------------------------------------------- 3. valgrind
say "3. Valgrind on every provided test"
if command -v valgrind > /dev/null; then
    for inp in in*.txt; do
        [ -e "$inp" ] || break
        if valgrind -q --leak-check=full --show-leak-kinds=all --error-exitcode=99 \
             "$BIN" < "$inp" > /dev/null 2> "vg_${inp%.txt}.log"; then
            ok "$inp: no errors, no leaks"
        else
            bad "$inp: Valgrind reported problems (see vg_${inp%.txt}.log)"
            grep -E "Invalid|definitely lost|indirectly lost|double free|uninitialised" "vg_${inp%.txt}.log" | head -5 | sed 's/^/      /'
        fi
    done
else
    echo "  valgrind not installed. Install:  sudo apt-get update && sudo apt-get install -y valgrind"
fi

# ---------------------------------------------------------------- 4. stress + independent oracle
say "4. Random stress tests checked against an independent sort"
if command -v python3 > /dev/null; then
    python3 check_order.py "$BIN" && ok "all generated cases match the reference ordering" || bad "a generated case disagreed with the reference (details above)"
else
    echo "  python3 not found, skipped"
fi

# ---------------------------------------------------------------- 5. sanitizers
say "5. AddressSanitizer + UndefinedBehaviorSanitizer build"
if gcc -w -g -fsanitize=address,undefined -fno-omit-frame-pointer "$SRC" -o mr_asan 2>/dev/null; then
    asan_bad=0
    for inp in in*.txt stress_*.txt; do
        [ -e "$inp" ] || continue
        if ! ./mr_asan < "$inp" > /dev/null 2> "asan_${inp%.txt}.log"; then
            bad "$inp under sanitizers (see asan_${inp%.txt}.log)"; asan_bad=1
        fi
    done
    [ $asan_bad -eq 0 ] && ok "no memory errors or undefined behaviour detected"
    rm -f mr_asan
else
    echo "  sanitizer build not supported on this compiler, skipped"
fi

# ---------------------------------------------------------------- summary
say "Summary"
printf '  %d passed, %d failed\n' "$PASS" "$FAIL"
[ $FAIL -eq 0 ] && echo "  Ready for a final compile-and-run on Eustis." || echo "  Fix the FAIL lines above, then re-run."
rm -f "$BIN"
exit $FAIL
