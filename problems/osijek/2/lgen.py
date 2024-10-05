#!/usr/bin/env python3

from random import randint, sample

N = int(5e3)
Q = int(4e6)
M = int(1e9)

print(1)
print(N, Q)
for i in range(N):
    print(randint(-M, M), randint(-M, M))
indices = [i+1 for i in range(N)]
for j in range(Q):
    print(*sample(indices, 3))
