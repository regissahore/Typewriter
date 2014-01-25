import random
from fractions import gcd

for t in range(1, 11):
    a = 2
    b = 2
    while gcd(a, b) != 1:
        a = random.randint(2, 2000000000)
        if t <= 4:
            b = random.randint(t * 2, 1000)
        elif t <= 6:
            b = random.randint((t - 4) * 10000000, 50000000)
        else:
            b = random.randint(1000000000, 2000000000)
    file = open("mod" + str(t) + ".in", "w")
    file.write(str(a) + " " + str(b) + "\n")
    file.close()
