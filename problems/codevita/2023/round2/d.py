#!/usr/bin/env python3

from datetime import datetime


N = int(input())
P = []
D = []
refday = None
for i in range(N):
    p, d = input().split()
    P.append(int(p))
    d = datetime.strptime(d, "%d-%b-%Y").date()
    if refday is not None:
        D.append((d - refday).days)
    else:
        D.append(0)
        refday = d


def func(rate) -> float:
    rate += 1
    x = 0
    for p, d in zip(P, D):
        x += p / rate ** (d / 365)
    return x


r = 0.1
for iter in range(500):
    # print(f"r at iter {iter}: {r}")

    cur = func(r)
    delta = 0.001
    nxt = func(r + delta)

    m = (nxt - cur) / delta
    r += -cur / m

print(round(r * 100, 2))
