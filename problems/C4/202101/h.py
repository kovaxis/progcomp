
h = input().split(' ')
h = h[1:]
for i in range(len(h)):
    h[i] = int(h[i])
b = input().split(' ')
b = b[1:]
for i in range(len(b)):
    b[i] = int(b[i])

count_to_buns = {}


def buy_b(idx, count, depth):
    count += b[idx]
    if count not in count_to_buns or depth < count_to_buns[count]:
        count_to_buns[count] = depth
    for i in range(idx + 1, len(b)):
        buy_b(i, count, depth + 1)


for i in range(len(b)):
    buy_b(i, 0, 1)


def buy_h(idx, count, depth, minimum):
    count += h[idx]
    if count in count_to_buns:
        packets = depth + count_to_buns[count]
        if packets < minimum:
            minimum = packets
    for i in range(idx + 1, len(h)):
        newmin = buy_h(i, count, depth + 1, minimum)
        if newmin < minimum:
            minimum = newmin
    return minimum


max_num = 999999
minimum = max_num
for i in range(len(h)):
    newmin = buy_h(i, 0, 1, minimum)
    if newmin < minimum:
        minimum = newmin

if minimum == max_num:
    print("impossible")
else:
    print(minimum)
