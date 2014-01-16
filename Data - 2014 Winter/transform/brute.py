t = int(input())
for k in range(0, t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    for i in range(1, len(a)):
        a[i] += a[i - 1]
    a.sort()
    for i in range(1, len(b)):
        b[i] += b[i - 1]
    b.sort()
    if a == b:
        print("YES")
    else:
        print("NO")
