#!/usr/bin/env python3

K = int(input())

if K == 1:
    print("199991")
else:
    print("199999" + (K - 1) * 10 * "1")
