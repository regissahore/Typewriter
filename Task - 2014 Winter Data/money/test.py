import os

for t in range(1, 11):
    inputName = "money" + str(t) + ".in"
    outputName = "money" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "money" + str(t) + ".in"
    outputName = "money" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
