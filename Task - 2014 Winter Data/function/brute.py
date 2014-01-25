for t in range(1, 11):
	fileRead = open("function" + str(t) + ".in", "r");
	fileWrite = open("function" + str(t) + ".out", "w");
	line = fileRead.readline().split(" ")
	a = int(line[0])
	b = int(line[1])
	n = int(fileRead.readline())
	count = 0
	for i in range(0, n):
		line = fileRead.readline().split(" ")
		x = int(line[0])
		y = int(line[1])
		if a * x + b == y:
		    count += 1
	print("Data " + str(t) + ": " + str(count))
	fileWrite.write(str(count) + "\n");
	fileRead.close()
	fileWrite.close()