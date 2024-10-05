#!/usr/bin/env python3

import sys
import math

A = list(map(int, sys.stdin.read().split()))[1:]
W = A.pop()
N = len(A)

if sum(A) < W:
    # NOTE: what to do in this case
    raise RuntimeError("not enough log distance")

UP = list(range(N // 2))
UP.sort(key=lambda i: A[i], reverse=True)
DN = list(range(N // 2 + 1, N))
DN.sort(key=lambda i: A[i], reverse=True)
G = [0.0 for i in range(N)]


def cos(deg):
    return math.cos(math.radians(deg))


def sin(deg):
    return math.sin(math.radians(deg))


def width():
    return sum(A[i] * cos(G[i]) for i in range(N))


MAX_ANG = 90


def angle_just_right(A, B, W):
    """
    Find angles a and b such that cos(a) * A + cos(b) * B = W, and sin(a) * A + sin(b) * B = 0
    """
    # Find the right height to solve:
    # sqrt(A^2 - h^2) + sqrt(B^2 - h^2) = W
    l = 0
    r = min(A, B)
    for iter in range(100):
        h = (l + r) / 2
        w = math.sqrt(A * A - h * h) + math.sqrt(B * B - h * h)
        if w > W:
            l = h
        elif w < W:
            r = h
    h = (l + r) / 2

    # Calculate angles based on height
    return math.degrees(math.asin(h / A)), -math.degrees(math.asin(h / B))


while True:
    missing = width() - W
    if missing <= 0:
        break

    while UP and abs(G[UP[-1]]) >= MAX_ANG:
        UP.pop()
    while DN and abs(G[DN[-1]]) >= MAX_ANG:
        DN.pop()
    if not UP or not DN:
        raise RuntimeError("logs too long")
    i = UP[-1]
    j = DN[-1]

    cur_w = A[i] * cos(G[i]) + A[j] * cos(G[j])
    target_w = cur_w - missing

    short = min(A[i], A[j])
    long = max(A[i], A[j])
    min_w = short * cos(MAX_ANG) + math.sqrt(long**2 - (short * sin(MAX_ANG)) ** 2)
    if target_w <= min_w:
        # Use the minimum possible length
        if A[i] < A[j]:
            # Raise left log straight up
            G[i] = MAX_ANG
            G[j] = -math.degrees(math.asin(sin(MAX_ANG) * short / long))
        elif A[i] > A[j]:
            # Lower right long straight down
            G[j] = -MAX_ANG
            G[i] = math.degrees(math.asin(sin(MAX_ANG) * short / long))
        else:
            # Both straight up/down
            G[i] = MAX_ANG
            G[j] = -MAX_ANG
    else:
        # Angle just right
        G[i], G[j] = angle_just_right(A[i], A[j], target_w)

print(" ".join("%.2f" % abs(ang) for ang in G))

# print(
#     f"destination: {sum(a * cos(round(g, 2)) for a, g in zip(A, G))}, {sum(a * sin(round(g, 2)) for a, g in zip(A, G))}"
# )
