def toString(n, num):
    res = ''
    while num != 0:
        res = str(num % n) + res;
        num = num // n;
    return res

for t in range(1, 11):
    fileRead = open("n" + str(t) + ".in", "r")
    fileWrite = open("n" + str(t) + ".out", "w")
    n = int(fileRead.readline())
    strs = fileRead.readline().split(" ")
    a = int(strs[0], n)
    b = int(strs[1], n)
    fileWrite.write(toString(n, a * b) + "\n")
    fileRead.close()
    fileWrite.close()
