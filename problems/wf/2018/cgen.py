#!/usr/bin/env python3

import random

N = int(5)
M = int(10)

print(N)
tree = [1]
for u in range(2, N + 1):
    parent = random.choice(tree)
    print(parent, u, random.randint(1, M))
    tree.append(u)

X = [0 for u in range(N)]
Y = [0 for u in range(N)]
Xtotal = random.randint(0, M)
Ytotal = random.randint(0, Xtotal)
for _ in range(Xtotal):
    X[random.randint(0, N - 1)] += 1
for _ in range(Ytotal):
    Y[random.randint(0, N - 1)] += 1
for u in range(N):
    print(X[u], Y[u])
