n = int(input())
a = []
for i in range(n):
    a.append(list(map(int, input().split(" "))))
m = int(input())
u = []
v = []
w = []
for i in range(m):
    tu, tv = map(int, input().split(" "))
    tu -= 1
    tv -= 1
    u.append(tu)
    v.append(tv)
    w.append(a[tu][tv])
    a[tu][tv] = 10 ** 10
ans = []
for k in range(n):
    for i in range(n):
        for j in range(n):
            if a[i][k] != 10 ** 10:
                if a[k][j] != 10 ** 10:
                    if a[i][j] > a[i][k] + a[k][j]:
                        a[i][j] = a[i][k] + a[k][j]
for k in range(m - 1, -1, -1):
    ans.append(sum([sum(a[i]) for i in range(n)]))
    tu = u[k]
    tv = v[k]
    if a[tu][tv] > w[k]:
        a[tu][tv] = w[k]
    if w[k] != 10 ** 10:
        for i in range(n):
            for j in range(n):
                if a[i][tu] != 10 ** 10:
                    if a[tv][j] != 10 ** 10:
                        if a[i][j] > a[i][tu] + a[tu][tv] + a[tv][j]:
                            a[i][j] = a[i][tu] + a[tu][tv] + a[tv][j]
for i in range(m - 1, -1, -1):
    if ans[i] >= 10 ** 10:
        print("INF")
    else:
        print(str(ans[i]))