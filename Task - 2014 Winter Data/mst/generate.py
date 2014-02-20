import random

for t in range(1, 11):
    file = open("mst" + str(t) + ".in", "w")
    if t <= 3:
        n = random.randint(t * 10, 100)
        m = random.randint(t * 100, 1000)
    else:
        n = random.randint(t * 1000, 10000)
        m = random.randint(t * 10000, 100000)
    file.write(str(n) + " " + str(m) + "\n")
    for i in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        a = random.randint(1, 10000)
        b = random.randint(1, 10000)
        file.write(str(u) + " " + str(v) + " " + str(a) + " " + str(b) + "\n")
    file.close()
