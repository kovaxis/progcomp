
n = int(input())
pokemons = input()

last = {}
start_of_all = 0
for i in range(n):
    ty = pokemons[i]
    if ty not in last:
        start_of_all = i
    last[ty] = 0

minlen = 100001
for i in range(n):
    ty = pokemons[i]
    last[ty] = i
    length = i + 1 - min(last.values())
    if i >= start_of_all and length < minlen:
        minlen = length

print(minlen)
