import random

for t in range(1, 11):
    file = open("translate" + str(t) + ".in", "w")
    if t <= 7:
        m = random.randint(t * 10, 100)
        n = random.randint(t * 100, 1000)
    else:
        m = random.randint(t * 5000, 50000)
        n = random.randint(t * 20000, 200000)
    k = int(m / 8)
    d = [random.randint(0, 1000000) for i in range(0, k)]
    file.write(str(m) + " " + str(n) + "\n")
    for i in range(0, n):
        if i > 0:
            file.write(" ")
        file.write(str(d[random.randint(0, k - 1)]))
    file.write("\n")
    file.close()
