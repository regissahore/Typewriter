import os

for t in range(1, 11):
    inputName = "translate" + str(t) + ".in"
    outputName = "translate" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "translate" + str(t) + ".in"
    outputName = "translate" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
