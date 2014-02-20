import random

for t in range(1, 11):
    file = open("prison" + str(t) + ".in", "w")
    if t <= 3:
        n = random.randint(t * 5, 15)
        m = random.randint(t * 10, 30)
    elif t <= 7:
        n = random.randint(t * 200, 2000)
        m = random.randint(t * 5000, 50000)
    else:
        n = random.randint(t * 2000, 20000)
        m = random.randint(t * 10000, 100000)
    file.write(str(n) + " " + str(m) + "\n")
    for i in range(n):
        u = random.randint(1, n)
        v = random.randint(1, n)
        w = random.randint(1, 100000)
        file.write(str(u) + " " + str(v) + " " + str(w) + "\n")
    file.close()
