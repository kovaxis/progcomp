#!/usr/bin/env python3

import re
import math
import sys

testcase = re.compile(r"^#\d{1,2}: ([^\]]+?) \[(\d+) ms, (\d+) MB, ([\d\.]+) points\]$")

Js = [
    2,
    266,
    498,
    801,
    356,
    150,
    120,
    160,
    710,
    180,
    255,
    380,
    80,
    822,
    185,
    572,
    354,
    150,
    120,
    160,
    830,
    181,
    127,
    255,
    80,
    838,
    184,
    282,
    355,
    150,
    120,
    160,
    1655,
    181,
    254,
    250,
    80,
    1658,
    185,
    806,
    358,
    150,
    120,
    160,
    835,
    182,
    255,
    380,
    80,
    826,
    184,
]

lines = sys.stdin.read().split("\n")

for tc in range(1, 51 + 1):
    mat = testcase.match(lines[tc - 1])
    assert mat
    status, ms, mb, score = mat.groups()
    if status != "Accepted":
        print(f"Test case {tc}: {status}")
    ms = int(ms)
    mb = int(mb)
    score = float(score)
    frames = math.ceil(score)
    percent = frames / Js[tc - 1]
    print(f"Test case {tc}: {round(percent*100, 2)}%")
