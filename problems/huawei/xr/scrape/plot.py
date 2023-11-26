#!/usr/bin/env python3

import csv
import parse
import matplotlib.pyplot as plt

bytc = [[] for _ in range(parse.N)]

with open("scrape/d.csv") as f:
    for row in csv.reader(f):
        for i in range(parse.N):
            bytc[i].append(float(row[i]))

percent = [p for p in range(101)]
for i, tc in enumerate(bytc):
    plt.clf()
    plt.plot(percent, tc)
    plt.title(f"Test Case #{i+1}")
    plt.xlabel("Percentile (%)")
    plt.ylabel("D")
    plt.savefig(f"scrape/out/ddistr/{i+1}.png")
