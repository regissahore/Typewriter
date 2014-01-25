for t in range(1, 11):
    file1 = open("n" + str(t) + ".out")
    file2 = open("n" + str(t) + ".test")
    if file1.readline() == file2.readline():
        print("Correct");
    file1.close()
    file2.close()
