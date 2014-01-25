import os

for t in range(1, 11):
    inputName = "expr" + str(t) + ".in"
    outputName = "expr" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "expr" + str(t) + ".in"
    outputName = "expr" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
