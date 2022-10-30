
import random

N = 100000
M = 100000
K = 20
MAXW = 1000000000

with open("input.txt", "w") as f:
    f.write(f"{N} {M} {K}\n")
    for i in range(M):
        u = random.randint(1, N)
        v = random.randint(1, N-1)
        if v >= u:
            v += 1
        w = random.randint(1, MAXW)
        f.write(f"{u} {v} {w}\n")
