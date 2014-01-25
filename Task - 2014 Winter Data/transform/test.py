import os

for t in range(1, 11):
    inputName = "transform" + str(t) + ".in"
    outputName = "transform" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "transform" + str(t) + ".in"
    outputName = "transform" + str(t) + ".test"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
