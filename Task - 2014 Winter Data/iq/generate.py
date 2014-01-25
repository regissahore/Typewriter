import random

chars = 'abcdefghijklmnopqrstuvwxyz'

for t in range(1, 10):
    file = open("iq" + str(t) + ".in", "w")
    n = random.randint(1, 100)
    m = random.randint(1, 100)
    k = random.randint(1, 100)
    if t > 4:
        n = random.randint(100, 1000)
        m = random.randint(100, 1000)
        k = random.randint(100, 1000)
    s = random.randint(90000, 100000)
    file.write(str(n) + " " + str(m) + " " + str(k) + " " + str(s) + "\n")
    for i in range(0, n):
        for j in range(0, m):
            if j > 0:
                file.write(" ")
            for k in range(0, 3):
                file.write(chars[random.randint(0, 25)])
        file.write('\n')
    file.close()

file = open("iq10.in", "w")
n = 1000
m = 1000
k = 99
s = 99999
file.write(str(n) + " " + str(m) + " " + str(k) + " " + str(s) + "\n")
for i in range(0, n):
    for j in range(0, m):
        if j > 0:
            file.write(" ")
        if i % 100 == 0 and j % 100 == 0:
            file.write("aaa")
        else:
            file.write("bbb")
    file.write('\n')
file.close()
