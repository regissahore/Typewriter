[a, b] = map(int, input().split())
x = 1
while (a * x) % b != 1:
    x += 1
print(x)
