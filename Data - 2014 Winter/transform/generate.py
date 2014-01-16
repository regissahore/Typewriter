import random

for t in range(1, 11):
    file = open("transform" + str(t) + ".in", "w")
    caseNum = random.randint(3, 5)
    file.write(str(caseNum) + "\n")
    for k in range(0, caseNum):
        if t <= 3:
            n = random.randint(t * 10, 100)
        else:
            n = random.randint(t * 500, 5000)
        file.write(str(n) + "\n")
        a = [i for i in range(0, n)]
        for i in range(0, n):
            if i > 0:
                file.write(' ')
            a[i] = random.randint(-100, 100)
            file.write(str(a[i]))
        file.write('\n')
        for i in range(0, 10000):
            pos = random.randint(1, n - 2)
            t1 = a[pos - 1] + a[pos]
            t2 = -a[pos]
            t3 = a[pos + 1] + a[pos]
            a[pos - 1] = t1
            a[pos] = t2
            a[pos + 1] = t3
        if random.randint(1, 3) > 1:
            a[random.randint(0, n - 1)] += 1
            a[random.randint(0, n - 1)] -= 1
        for i in range(0, n):
            if i > 0:
                file.write(' ')
            file.write(str(a[i]))
        file.write('\n')
    file.close()
