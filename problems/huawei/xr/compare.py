#!/usr/bin/env python3

from pathlib import Path
import parse
import sys

tests1 = parse.parse(Path(sys.argv[1]).read_text())
tests2 = parse.parse(Path(sys.argv[2]).read_text())

ok = 0
power = 0
for test1, test2 in zip(tests1, tests2):
    if test2.frames() < test1.frames():
        print(f"Regression in test {test1.number}: {test1.score} -> {test2.score}")
    elif test2.score < test1.score:
        power += 1
    else:
        ok += 1

print(f"{ok} testcases improved or stayed the same")
print(f"{power} testcases remain the same but consume more power")
