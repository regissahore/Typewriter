import random

for t in range(1, 11):
    file = open("destroy" + str(t) + ".in", "w")
    if t <= 4:
        n = random.randint(t * 5, 50)
        m = random.randint(t * 5, 50)
    else:
        n = random.randint(t * 20, 200)
        m = random.randint(t * 20, 200)
    file.write(str(n) + "\n")
    d = [["0" for j in range(n)] for i in range(n)]
    for i in range(0, n):
        for j in range(0, n):
            if i == j:
                d[i][j] = "0"
            else:
                d[i][j] = str(random.randint(1, 10000))
    for i in range(0, n):
        file.write(" ".join(d[i]) + "\n")
    file.write(str(m) + "\n")
    for i in range(0, m):
        while True:
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v:
                break
        file.write(str(u) + " " + str(v) + "\n")
    file.close()
