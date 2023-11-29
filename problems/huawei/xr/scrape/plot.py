#!/usr/bin/env python3

import csv
from pathlib import Path
import parse
import matplotlib.pyplot as plt
import sys

args = sys.argv[1:]

if len(args) < 3:
    print("usage: plot <variable name> <csv input> <output folder>")
    sys.exit()

varname, inpath, outpath = args
outpath = Path(outpath)
outpath.mkdir(exist_ok=True)


bytc = [[] for _ in range(parse.N)]

samples = 0
with open(inpath) as f:
    for row in csv.reader(f):
        samples += 1
        for i in range(parse.N):
            bytc[i].append(float(row[i]))


percent = [round(100 * p / (samples - 1)) for p in range(samples)]
for i, tc in enumerate(bytc):
    plt.clf()
    plt.plot(percent, tc)
    plt.title(f"Test Case #{i+1}")
    plt.xlabel("Percentile (%)")
    plt.ylabel(varname)
    plt.yscale("log")
    plt.savefig(outpath.joinpath(f"{i+1}.png"))

print(f"plotted {samples} samples over {parse.N} testcases to {outpath}")
