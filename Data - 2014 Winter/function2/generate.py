import random

for t in range(1, 11):
    while True:
        x1 = random.randint(-1000, 1000)
        if t <= 3:
            x2 = x1
            x3 = x1
        else:
            x2 = random.randint(-1000, 1000)
            x3 = random.randint(-1000, 1000)
        while True:
            k = random.randint(-5, 5)
            if k != 0:
                break
        a = k;
        b = -k * (x1 + x2 + x3);
        c = k * (x1 * x2 + x2 * x3 + x3 * x1)
        d = -k * x1 * x2 * x3
        if b in range(-10 ** 9, 10 ** 9 + 1):
            if c in range(-10 ** 9, 10 ** 9 + 1):
                if d in range(-10 ** 9, 10 ** 9 + 1):
                    break
    file = open("function2" + str(t) + ".in", "w")
    file.write(str(a) + " " + str(b) + " " + str(c) + " " + str(d) + "\n")
    file.close()

