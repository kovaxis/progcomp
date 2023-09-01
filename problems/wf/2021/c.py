N, M = map(int, input().split())

q = 2
ans_p = -1
ans_q = -1
while True:
    anysmall = False
    r = 1
    while r < q:
        p = q - r
        num = M * p
        den = q**N - (q-p)**N
        if num % den == 0:
            ans_p = p
            ans_q = q
        if den <= num:
            anysmall = True
            if num % den == 0:
                anysmall = False
                break
        else:
            break
        r += 1
    if not anysmall:
        break
    q += 1

if ans_q == -1:
    print("impossible")
else:
    print(p, q)
