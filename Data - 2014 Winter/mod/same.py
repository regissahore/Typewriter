for t in range(1, 11):
    file1 = open("mod" + str(t) + ".out")
    file2 = open("mod" + str(t) + ".test")
    print(file1.readline()[:-1] + " " + file2.readline()[:-1])
    file1.close()
    file2.close()
