[a, b, c, d] = map(int, input().split())
x = [str(x) for x in range(-1000, 1001) if ((a * x + b) * x + c) * x + d == 0]
print(' '.join([str(x) for x in range(-1000, 1001) if ((a * x + b) * x + c) * x + d == 0]))
