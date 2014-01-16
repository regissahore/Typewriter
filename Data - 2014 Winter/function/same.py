for t in range(1, 11):
    file1 = open("function" + str(t) + ".out")
    file2 = open("function" + str(t) + ".test")
    print(file1.readline()[:-1] + " " + file2.readline()[:-1])
    file1.close()
    file2.close()
