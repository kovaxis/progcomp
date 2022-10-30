for i in range(int(input())):
    n, k = input().split(" ")
    n = int(n)
    k = int(k)
    s = input()

    arr = []
    for j in range(n):
        if s[j] == '0':
            arr.append(False)
        elif s[j] == '1':
            arr.append(True)
        else:
            arr.append(None)

    while True:
        changed = False
        for start in range(n - k + 1):
            zeroes = 0
            ones = 0
            unknowns = 0
            for j in range(start, start + k):
                if arr[j] == None:
                    unknowns += 1
                elif arr[j]:
                    ones += 1
                else:
                    zeroes += 1
            if unknowns != 0:
                if zeroes + unknowns == ones:
                    for j in range(start, start + k):
                        if arr[j] == None:
                            arr[j] = False
                    changed = True
                elif ones + unknowns == zeroes:
                    for j in range(start, start + k):
                        if arr[j] == None:
                            arr[j] = True
                    changed = True
        if not changed:
            break

    unknowns = []
    unkvals = []
    for j in range(n):
        if arr[j] == None:
            unknowns.append(j)
            unkvals.append(False)

    all_ok = True
    while True:
        for j in range(len(unknowns)):
            arr[unknowns[j]] = unkvals[j]

        all_ok = True
        for start in range(n - k + 1):
            zeroes = 0
            ones = 0
            for j in range(start, start + k):
                if arr[j]:
                    ones += 1
                else:
                    zeroes += 1
            if zeroes != ones:
                all_ok = False
                break

        if all_ok:
            break

        for j in range(len(unknowns)):
            if not unkvals[j]:
                unkvals[j] = True
                break
            else:
                unkvals[j] = False
        else:
            break

    if all_ok:
        print("YES")
    else:
        print("NO")
