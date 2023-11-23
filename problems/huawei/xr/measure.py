#!/usr/bin/env python3

import sys
import parse

tests = parse.parse(sys.stdin.read())

for test in tests:
    print(
        f"Test case {test.number}: {round(100 * test.frames() / test.perfect_score(), 2)}%"
    )
