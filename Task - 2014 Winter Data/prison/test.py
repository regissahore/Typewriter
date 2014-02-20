import os

for t in range(1, 11):
    inputName = "prison" + str(t) + ".in"
    outputName = "prison" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);
