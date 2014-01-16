import random

def getRandom(t):
    if t == 1:
        return random.randint(0, 10 ** 2)
    if t <= 7:
        return random.randint(10 ** 499, 10 ** 500)
    return random.randint(10 ** 49999, 10 ** 50000)

for t in range(1, 11):
    print("Generate data " + str(t) + "...")
    a = getRandom(t);
    b = getRandom(t);
    n = 10;
    if t <= 7:
        n = 5;
    file = open('function' + str(t) + ".in", "w")
    file.write(str(a) + " " + str(b) + "\n" + str(n) + "\n")
    for i in range(0, n):
        x = getRandom(t)
        y = a * x + b;
        if random.randint(0, 9) < 5:
            if random.randint(0, 9) < 4:
                y += getRandom(t)
            else:
                y -= getRandom(t)
        file.write(str(x) + " " + str(y) + "\n")
    file.close()
