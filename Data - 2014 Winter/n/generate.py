import random

for t in range(1, 11):
    file = open("n" + str(t) + ".in", "w")
    n = random.randint(2, 9)
    m = 4
    if t > 4:
        m = 1000
    a = ''
    b = ''
    for i in range(0, m):
        a += str(random.randint(0, n - 1))
        b += str(random.randint(0, n - 1))
    file.write(str(n) + "\n");
    file.write(a + " " + b + "\n")
    file.close()
