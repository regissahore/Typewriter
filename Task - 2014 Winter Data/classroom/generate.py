import random

for t in range(1, 11):
    if t <= 1:
        n = random.randint(t, 10)
        m = random.randint(t, 10)
    elif t <= 3:
        n = random.randint(t * 100, 1000)
        m = random.randint(t * 100, 1000)
    elif t <= 7:
        n = random.randint(t * 10000, 100000)
        m = random.randint(t * 10000, 100000)
    else:
        n = random.randint(t * 100000, 1000000)
        m = random.randint(t * 100000, 1000000)
    file = open("classroom" + str(t) + ".in", "w")
    file.write(str(n) + " " + str(m) + "\n")
    for i in range(0, n):
        if i > 0:
            file.write(" ")
        file.write(str(random.randint(m, 10 ** 9)))
    file.write("\n");
    for i in range(0, m):
        while True:
            s = random.randint(1, n)
            t = random.randint(1, n)
            if s <= t:
                break
        if i < m - 100:
            if random.randint(1, 1000) == 1:
                d = 2
            else:
                d = 1
        else:
            d = random.randint(1, 10 ** 9)
        file.write(str(d) + " " + str(s) + " " + str(t) + "\n")
    file.close()
