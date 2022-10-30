
n = int(input())

papers = [int(input()) for i in range(n)]
papers.sort(reverse=False)

h = 0
for i in range(n):
    if n - i <= h:
        break
    this_h = min(n - i, papers[i])
    if this_h > h:
        h = this_h

print(h)
