#!/usr/bin/env python3

from functools import cache
import math


@cache
def dp_acc(d, k, skipzero):
    if d == 0:
        if skipzero:
            return 0
        else:
            return k
    acc = (
        dp_acc(d - 1, k, skipzero)
        + dp_acc(d - 1, k - 1, False)
        + 8 * dp_acc(d - 1, k, False)
    )
    # print(f"dp_acc[{d}, {k}, {skipzero}] = {acc}")
    return acc


@cache
def dp_min(d, k, skipzero):
    if d == 0:
        if skipzero:
            return math.inf
        else:
            return k
    mn = dp_min(d - 1, k, skipzero)
    mn = min(mn, dp_acc(d - 1, k, skipzero) + dp_min(d - 1, k - 1, False))
    for i in range(2, 10):
        mn = min(
            mn,
            dp_acc(d - 1, k, skipzero)
            + dp_acc(d - 1, k - 1, False)
            + (i - 2) * dp_acc(d - 1, k, False)
            + dp_min(d - 1, k, False),
        )
    # print(f"dp_min[{d}, {k}, {skipzero}] = {mn}")
    return mn


ans = ""


def find(d, k, skipzero, acc):
    global ans

    if d == 0:
        return
    if acc + dp_min(d - 1, k, skipzero) < 0:
        ans += "0"
        return find(d - 1, k, skipzero, acc)
    acc += dp_acc(d - 1, k, skipzero)
    if acc + dp_min(d - 1, k - 1, False) < 0:
        ans += "1"
        return find(d - 1, k - 1, False, acc)
    acc += dp_acc(d - 1, k - 1, False)
    for i in range(2, 10):
        if acc + dp_min(d - 1, k, False) < 0:
            ans += str(i)
            return find(d - 1, k, False, acc)
        acc += dp_acc(d - 1, k, False)
    raise RuntimeError("acc is never negative?")


K = int(input())

find(300, K, True, 0)
ans = int(ans)

print(ans)
