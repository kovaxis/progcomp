import os
import subprocess
import random

os.system("g++ -std=c++11 -o tmp.exe c.cpp")
print("compiled")

f = open("input.txt", "w+")
iteration = 0
while True:
    f.seek(0)
    f.truncate()
    n = random.randint(1, 5*10**5)
    parts = [random.randint(-10**9, 10**9) for i in range(n)]
    parts.sort()
    last_pos = None
    for i in range(n-1, -1, -1):
        if parts[i] == last_pos:
            parts.pop(i)
        else:
            last_pos = parts[i]
    n = len(parts)
    f.write(f"{n}\n")
    for pos in parts:
        vel = 0
        while vel == 0:
            vel = random.randint(-10**9, 10**9)
        f.write(f"{pos} {vel}\n")
    f.flush()

    f.seek(0)
    p = subprocess.Popen(["./tmp.exe"], stdout=None, stdin=f)
    p.wait()
    iteration += 1
    print(f"iteration {iteration}")
