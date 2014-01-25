import random

for t in range(1, 11):
    file = open("money" + str(t) + ".in", "w")
    if t <= 3:
        n = random.randint(t * 100, 1000)
    else:
        n = random.randint(t * 30000, 300000)
    file.write(str(n) + '\n')
    for i in range(n):
        if i > 0:
            file.write(' ')
        file.write(str(random.randint(1, 1000000000)))
    file.write('\n')
    file.close()
