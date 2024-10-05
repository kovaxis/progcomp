#!/usr/bin/env python3

# Take adjacent K values, ignoring voids

D = list(map(int, input().split()))
A = [0, 0]
B = [0, 0]
A[0], B[0] = map(int, input().split())
A[1], B[1] = map(int, input().split())
K = int(input().strip())


def toggle(x):
    # TODO: what if x = 0? y = 1 or y = 0?
    return int("".join(str(1 - int(c)) for c in bin(x)[2:]))


scores = [0, 0]
turn = 1
while True:
    turn = 1 - turn

    mx_i = 0
    for i in range(len(D)):
        if D[mx_i] is None or (D[i] is not None and D[i] > D[mx_i]):
            mx_i = i
    if D[mx_i] is None:
        break

    for i in range(max(mx_i - K, 0), min(mx_i + K + 1, len(D))):
        if D[i] is not None:
            # print(f"player {turn} is taking value {D[i]}")
            scores[turn] += D[i]
        D[i] = None

# print(f"rahul sum: {scores[0]}")
# print(f"rupesh sum: {scores[1]}")

if scores[0] > scores[1]:
    mx_score = 0
else:
    mx_score = 1
A[mx_score] = toggle(A[mx_score])
B[turn] = toggle(B[turn])

if A[0] ^ B[0] >= A[1] ^ B[1]:
    print("Rahul")
if A[0] ^ B[0] <= A[1] ^ B[1]:
    print("Rupesh")
