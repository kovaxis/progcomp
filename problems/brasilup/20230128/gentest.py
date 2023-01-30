#!/usr/bin/env python3

import random
from datetime import datetime
import sys

print("M:", file=sys.stderr)
m = int(input())
print("N:", file=sys.stderr)
n = int(input())
points = []


seed = round(datetime.now().timestamp())
random.seed(seed)
print(f"using seed = {seed}", file=sys.stderr)

for x in range(1, m):
    for y in range(1, m):
        points.append((x, y))

points = random.sample(points, n)

print(f"{m} {n}")
for x, y in points:
    print(f"{x} {y}")
