[m, n] = map(int, input().split())
lists = list(map(int, input().split()))
queue = []
count = 0
for i in range(0, len(lists)):
    if not lists[i] in queue:
        if len(queue) == m:
            queue = queue[1:]
        queue.append(lists[i])
        count += 1
print(count)
