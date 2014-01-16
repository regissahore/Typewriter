import random

for t in range(1, 11):
    file = open("juel" + str(t) + ".in", "w")
    n = random.randint(t, 15)
    file.write(str(n) + "\n")
    for i in range(0, n):
        if i > 0:
            file.write(" ")
        file.write(str(random.randint(1, 10)))
    file.write("\n")
    file.close()
