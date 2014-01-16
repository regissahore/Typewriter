import os

for t in range(1, 11):
    inputName = "game" + str(t) + ".in"
    outputName = "game" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "game" + str(t) + ".in"
    outputName = "game" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
