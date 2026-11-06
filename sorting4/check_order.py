"""check_order.py — generates random monster inputs, runs the compiled program on each,
and compares its output with a reference ranking computed by Python's own sort.

Usage: python3 check_order.py ./mr_test
The reference uses the assignment's rule directly (larger score first, then name),
so it is independent of merge sort, quick sort, and insertion sort.
"""
import random, subprocess, sys, time

prog = sys.argv[1] if len(sys.argv) > 1 else "./mr_test"
random.seed(2026)
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

def make_case(n, name_len=(1, 30), score_max=1000):
    names, rows = set(), []
    while len(rows) < n:
        nm = "".join(random.choice(LETTERS) for _ in range(random.randint(*name_len)))
        if nm in names:
            continue
        names.add(nm)
        el = "".join(random.choice(LETTERS) for _ in range(random.randint(1, 30)))
        p, s, t = (random.randint(0, score_max) for _ in range(3))
        rows.append((nm, el, p, s, t))
    return rows

def expected(rows):
    mons = [(nm, p + s + t, s) for nm, el, p, s, t in rows]
    ov = sorted(mons, key=lambda m: (-m[1], m[0]))
    sp = sorted(mons, key=lambda m: (-m[2], m[0]))
    out = ["Overall Expedition Ranking"]
    out += [f"{i + 1}. {m[0]:<15} {m[1]}" for i, m in enumerate(ov)]
    out += ["", "Speed Challenge Ranking"]
    out += [f"{i + 1}. {m[0]:<15} {m[2]}" for i, m in enumerate(sp)]
    return "\n".join(out) + "\n"

cases = [
    ("N=1",                      make_case(1)),
    ("N=30 (exactly base case)", make_case(30)),
    ("N=31 (first recursion)",   make_case(31)),
    ("N=61 (two levels)",        make_case(61)),
    ("N=1000",                   make_case(1000)),
    ("N=2000 heavy ties (scores 0..3)", make_case(2000, name_len=(1, 8), score_max=3)),
    ("N=500 all scores equal",   [(f"Name{i:04d}", "El", 7, 7, 7) for i in range(500)]),
    ("N=40 30-char names",       make_case(40, name_len=(30, 30))),
    ("N=100000 stress",          make_case(100000)),
]

all_ok = True
for label, rows in cases:
    text = f"{len(rows)}\n" + "".join(f"{nm} {el} {p} {s} {t}\n" for nm, el, p, s, t in rows)
    fname = f"stress_{label.split()[0].replace('=', '')}.txt"
    with open(fname, "w") as f:
        f.write(text)
    t0 = time.time()
    try:
        res = subprocess.run([prog], input=text, capture_output=True, text=True, timeout=30)
    except subprocess.TimeoutExpired:
        print(f"  FAIL {label}: timed out after 30 s"); all_ok = False; continue
    dt = time.time() - t0
    exp = expected(rows)
    if res.returncode != 0:
        print(f"  FAIL {label}: exit code {res.returncode}"); all_ok = False
    elif res.stdout != exp:
        got, want = res.stdout.split("\n"), exp.split("\n")
        first = next((i for i in range(min(len(got), len(want))) if got[i] != want[i]), min(len(got), len(want)))
        print(f"  FAIL {label}: first difference at output line {first + 1}")
        print(f"        got:      {got[first] if first < len(got) else '<missing>'}")
        print(f"        expected: {want[first] if first < len(want) else '<missing>'}")
        all_ok = False
    else:
        print(f"  ok   {label:36s} {dt * 1000:7.1f} ms   (input saved as {fname})")

# determinism: random pivots must never change the output
text = open("stress_N1000.txt").read()
outs = {subprocess.run([prog], input=text, capture_output=True, text=True).stdout for _ in range(5)}
if len(outs) == 1:
    print("  ok   5 repeated runs on N=1000 gave identical output (pivot randomness does not leak)")
else:
    print("  FAIL repeated runs gave different outputs: the ordering depends on the pivot"); all_ok = False

sys.exit(0 if all_ok else 1)
