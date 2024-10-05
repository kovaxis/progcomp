#!/usr/bin/env python3

import sys

approach = "3"
dolog = len(sys.argv) >= 2 and sys.argv[1] == "dologginglocally"


def log(*args):
    if dolog:
        print(*args)


def inputline():
    while True:
        line = input()
        if line:
            return line


D = list(map(int, inputline().split()))
A = [0, 0]
B = [0, 0]
A[0], B[0] = map(int, inputline().split())
A[1], B[1] = map(int, inputline().split())
K = int(inputline().strip())


def toggle(x):
    # TODO: what if x = 0? y = 1 or y = 0?
    return int("".join(str(1 - int(c)) for c in bin(x)[2:]))


def take(i):
    if D[i] is None:
        return 0
    else:
        log(f'{["rahul", "rupesh"][turn]} is taking value {D[i]}')
        scores[turn] += D[i]
        D[i] = None
        return 1


scores = [0, 0]
turn = 1
while True:
    mx_i = 0
    for i in range(len(D)):
        if D[mx_i] is None or (D[i] is not None and D[i] > D[mx_i]):
            mx_i = i
    if D[mx_i] is None:
        break

    turn = 1 - turn

    if approach == "1":
        take(mx_i)
        n = 0
        i = mx_i
        while n < K:
            i -= 1
            if i < 0:
                break
            n += take(i)
        n = 0
        i = mx_i
        while n < K:
            i += 1
            if i >= len(D):
                break
            n += take(i)
    if approach == "2":
        take(mx_i)
        l = mx_i
        r = mx_i
        for k in range(K):
            while l > 0:
                l -= 1
                if D[l] is not None:
                    break
            while r < len(D) - 1:
                r += 1
                if D[r] is not None:
                    break
            if D[l] is not None and D[r] is not None:
                take(l)
                take(r)
    if approach == "3":
        take(mx_i)
        l = mx_i
        r = mx_i
        for k in range(K):
            while l > 0:
                l -= 1
                if D[l] is not None:
                    break
            if D[l] is None:
                break
            take(l)
            while r < len(D) - 1:
                r += 1
                if D[r] is not None:
                    break
            if D[r] is None:
                break
            take(r)

log(f"rahul sum: {scores[0]}")
log(f"rupesh sum: {scores[1]}")

log(f"initial rahul A: {A[0]}")
log(f"initial rahul B: {B[0]}")
log(f"initial rupesh A: {A[1]}")
log(f"initial rupesh B: {B[1]}")

for k in range(2):
    if scores[k] >= scores[1 - k]:
        A[k] = toggle(A[k])
B[turn] = toggle(B[turn])

log(f"rahul A: {A[0]}")
log(f"rahul B: {B[0]}")
log(f"rupesh A: {A[1]}")
log(f"rupesh B: {B[1]}")

a = A[0] ^ B[0]
b = A[1] ^ B[1]
log(f"rahul score: {a}")
log(f"rupesh score: {b}")
if a >= b:
    print("Rahul")
if a <= b:
    print("Rupesh")
