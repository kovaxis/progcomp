
t_count = int(input())

coords = {}
l0 = 'qwertyuiop'
l1 = 'asdfghjkl'
l2 = 'zxcvbnm'
for i in range(len(l0)):
    coords[l0[i]] = [i, 0]
for i in range(len(l1)):
    coords[l1[i]] = [i, 1]
for i in range(len(l2)):
    coords[l2[i]] = [i, 2]

for i in range(t_count):
    [base_word, l_count] = input().split(' ')
    words = []
    l_count = int(l_count)
    for j in range(l_count):
        word = input()
        dist = 0
        for k in range(len(base_word)):
            base_c = base_word[k]
            c = word[k]
            if base_c != c:
                [x0, y0] = coords[base_c]
                [x1, y1] = coords[c]
                dist += abs(x0 - x1) + abs(y0 - y1)
        words.append((dist, word))
    words.sort()
    for (d, w) in words:
        print(f"{w} {d}")
