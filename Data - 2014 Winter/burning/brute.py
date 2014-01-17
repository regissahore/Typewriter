[a, b, c] = map(int, input().split())
ans = 0
d = 0
while a > 0:
    ans += a * b
    d += a
    a = d // c
    d -= a * c
print(ans)
