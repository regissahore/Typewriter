import os

for t in range(1, 11):
    inputName = "juel" + str(t) + ".in"
    outputName = "juel" + str(t) + ".test"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "juel" + str(t) + ".in"
    outputName = "juel" + str(t) + ".out"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
