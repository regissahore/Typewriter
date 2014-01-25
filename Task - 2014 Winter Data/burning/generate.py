import random

for t in range(1, 11):
    file = open("burning" + str(t) + ".in", "w")
    a = random.randint(1, 1000)
    b = random.randint(1, 1000)
    c = random.randint(1, 1000)
    file.write(str(a) + ' ' + str(b) + ' ' + str(c) + "\n")
    file.close()
