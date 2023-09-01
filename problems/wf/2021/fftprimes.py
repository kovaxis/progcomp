#!/usr/bin/env python3

from miller_rabin import miller_rabin as isprime

def prime(c, k):
    return c * (1 << k) + 1

def get_max_k(c, upper_bound):
    K = None
    k = 0
    while True:
        m = prime(c, k)
        if m > upper_bound:
            break
        if isprime(m):
            K = k
        k += 1
    return K

def get_max_m(min_k, upper_bound, max_c = None):
    if max_c is None:
        max_c = upper_bound - 1
    max_m = 0
    max_mc = 0
    max_mk = 0
    for c in range(1, max_c+1, 2):
        k = get_max_k(c, upper_bound)
        if k is not None and k >= min_k:
            m = prime(c, k)
            if m > max_m:
                max_m, max_mc, max_mk = m, c, k
    return max_mc, max_mk

c, k = get_max_m(20, (1<<63)-1, 1000000)

def print_max_m(min_k, max_m):
    c, k = get_max_m(min_k, max_m, 1000000)
    print(f"largest FFT modulus under {max_m} and with N >= 2^{min_k}:")
    if c == 0:
        print("  not found")
    else:
        print(f"  {prime(c, k)}, c = {c}, k = {k}")


print_max_m(20, (1<<63)-1)
print_max_m(20, (1<<62))
print_max_m(20, (1<<31)-1)
