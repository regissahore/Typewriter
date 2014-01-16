import random

for t in range(1, 11):
    if t <= 3:
        n = random.randint(t * 10, 100)
    elif t <= 8:
        n = random.randint(t * 100, 1000)
    else:
        n = random.randint(t * 10000, 100000)
    file = open("expr" + str(t) + ".in", "w")
    file.write(str(random.randint(0, 100000)))
    for i in range(0, n):
        if random.randint(0, 2) == 0:
            file.write("*")
        else:
            file.write("+")
        file.write(str(random.randint(0, 100000)))
    file.write("\n")
    file.close()
