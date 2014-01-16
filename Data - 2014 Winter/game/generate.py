import random

for t in range(1, 11):
    file = open("game" + str(t) + ".in", "w")
    if t <= 2:
        n = random.randint(t, 10)
    elif t <= 4:
        n = random.randint(t * 2, 20)
    elif t <= 6:
        n = random.randint(t * 10, 100)
    else:
        n = random.randint(t * 100, 1000)
    file.write(str(n) + "\n")
    for i in range(0, n + 1):
        if t <= 4:
            a = random.randint(1, 5)
            b = random.randint(1, 7)
        elif t <= 6:
            a = random.randint(1, 2)
            b = random.randint(9000, 10000)
        else:
            a = random.randint(1, 10000)
            b = random.randint(1, 10000)
        file.write(str(a) + " " + str(b) + "\n")
    file.close()
