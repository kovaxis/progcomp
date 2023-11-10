import random

R = 3000
C = 6000
print(R, C)
for i in range(R):
    print("x" + "---x" * (C // 2))
    print(" \\ /" * (C // 2))
    print("  x" + "   x" * (C // 2))
    print(" / \\" * (C // 2))
