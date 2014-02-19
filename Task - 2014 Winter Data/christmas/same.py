for t in range(1, 11):
    file1 = open("christmas" + str(t) + ".out")
    file2 = open("christmas" + str(t) + ".test")
    while True:
        str1 = file1.readline()
        str2 = file2.readline()
        if not str1:
            break
        if str1 != str2:
            print("Error " + str(t))
            break
    file1.close()
    file2.close()
