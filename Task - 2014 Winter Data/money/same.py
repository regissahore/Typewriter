for t in range(1, 11):
    file1 = open("money" + str(t) + ".out")
    file2 = open("money" + str(t) + ".test")
    while True:
        str1 = file1.readline()
        str2 = file2.readline()
        if not str1:
            break
        print(str1[:-1] + " " + str2[:-1])
    print()
    file1.close()
    file2.close()
