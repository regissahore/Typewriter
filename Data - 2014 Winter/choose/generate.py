import random

for t in range(1, 11):
    file = open("choose" + str(t) + ".in", "w")
    if t <= 3:
        m = random.randint(t * 100, 1000)
        n = random.randint(t * 100, 1000)
    else:
        m = random.randint(t * 10000, 100000)
        n = random.randint(t * 10000, 100000)
    file.write(str(m) + " " + str(n) + "\n")
    for i in range(0, m):
        if i > 0:
            file.write(" ")
        file.write(str(random.randint(0, 10 ** 9)))
    file.write("\n")
    for i in range(0, n):
        if i > 0:
            file.write(" ")
        file.write(str(random.randint(0, 10 ** 9)))
    file.write("\n")
    file.close()
