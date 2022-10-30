
line = ""
while True:
    try:
        line = input()
    except:
        break

    ints = line.split(' ')
    s = 0
    for i in ints:
        s += int(i)
    print(s // 2)
