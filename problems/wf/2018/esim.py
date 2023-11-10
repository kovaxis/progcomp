#!/usr/bin/env python3

import math
import sys


def f(tx, ty, v, alpha):
    d = v**2 * ty + alpha * tx**2
    print(f"d = {d}")
    a = tx**2 + ty**2
    b = -2 * d * ty - (tx**2) * (v**2)
    c = d**2
    print(f"a = {a}")
    print(f"b = {b}")
    print(f"c = {c}")
    disc = b**2 - 4 * a * c
    print(f"disc = {disc}")
    z = (-b + math.sqrt(disc)) / (2 * a)
    print(f"z = {z}")
    vy = math.sqrt(z)
    print(f"vy = {vy}")
    vx = math.sqrt(v**2 - vy**2)
    print(f"vx = {vx}")

    print(f"mag(vx, vy) = {math.sqrt(vx**2+vy**2)}")
    t = tx / vx
    print(f"t = {t}")
    print(f"x(t) = {vx * t}")
    print(f"y(t) = {vy*t - alpha*t**2}")

    return vx, vy


f(*map(float, sys.argv[1:]))
