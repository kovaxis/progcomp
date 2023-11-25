#!/usr/bin/env python3

from pathlib import Path
import parse
import sys

tests1 = parse.parse(Path(sys.argv[1]).read_text())
tests2 = parse.parse(Path(sys.argv[2]).read_text())

improve = 0
regress = 0
power_improve = 0
power_regress = 0
exact_same = 0
for test1, test2 in zip(tests1, tests2):
    if test2.frames() < test1.frames():
        print(f"Regression in test {test1.number}: {test1.score} -> {test2.score}")
        regress += 1
    elif test2.frames() > test1.frames():
        improve += 1
    elif test2.score < test1.score:
        power_regress += 1
    elif test2.score > test1.score:
        power_improve += 1
    else:
        exact_same += 1

if regress:
    print(f"{regress} testcases regressed")
if improve:
    print(f"{improve} testcases improved")
if power_improve:
    print(f"{power_improve} testcases stayed the same but consume less power")
if power_regress:
    print(f"{power_regress} testcases stayed the same but consume more power")
if exact_same:
    print(f"{exact_same} tests remain the exact same")
