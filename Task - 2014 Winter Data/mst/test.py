import os

for t in range(1, 11):
    inputName = "mst" + str(t) + ".in"
    outputName = "mst" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);
