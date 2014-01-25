n = int(input())
[left, right] = map(int, input().split())
a = []
b = []
for i in range(n):
    [ta, tb] = map(int, input().split())
    a.append(ta)
    b.append(tb)
for i in range(n):
    for j in range(i + 1, n):
        if a[i] * b[i] > a[j] * b[j]:
            temp = a[i]
            a[i] = a[j]
            a[j] = temp
            temp = b[i]
            b[i] = b[j]
            b[j] = temp
maxMoney = 0
for i in range(n):
    maxMoney = max(maxMoney, left // b[i])
    left *= a[i]
print(maxMoney)
