import os

for t in range(1, 11):
    inputName = "classroom" + str(t) + ".in"
    outputName = "classroom" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "classroom" + str(t) + ".in"
    outputName = "classroom" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
