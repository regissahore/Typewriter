n = int(input())
a = list(map(int, input().split()))
a.sort()
last = 0
ans = 0
for i in range(n):
    if a[i] <= last:
        last += 1
    else:
        last = a[i]
    ans += last
print(ans)
