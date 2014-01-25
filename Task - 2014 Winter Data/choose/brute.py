[m, n] = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))
A.sort()
total = 0
for b in B:
    l = 0
    r = len(A) - 1
    mini = 10 ** 10
    while l <= r:
        mid = (l + r) // 2
        mini = min(mini, abs(b - A[mid]))
        if b > A[mid]:
            l = mid + 1
        else:
            r = mid - 1
    total += mini
print(total)
