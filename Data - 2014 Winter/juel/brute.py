n = int(input())
a = list(map(int, input().split()))
a.sort()
total = 0
valid = 1
for i in range(n - 1, -1, -1):
    total += valid
    valid *= a[i]
print(total + valid)
