import os

for t in range(1, 11):
    inputName = "mod" + str(t) + ".in"
    outputName = "mod" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "mod" + str(t) + ".in"
    outputName = "mod" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
