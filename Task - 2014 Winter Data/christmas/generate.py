import random

for t in range(1, 11):
    file = open("christmas" + str(t) + ".in", "w")
    if t <= 3:
        q = random.randint(t * 300, 1000)
    else:
        q = random.randint(t * 50000, 500000)
    file.write(str(q) + "\n")
    leaf = {0: False, 1: False, 2: True, 3: True, 4: True}
    for i in range(q):
        while True:
            v = random.randint(2, len(leaf) - 1)
            if leaf[v]:
                break
        leaf[v] = False
        leaf[i * 2 + 5] = True
        leaf[i * 2 + 6] = True
        file.write(str(v) + "\n")
    file.close()
