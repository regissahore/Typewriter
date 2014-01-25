import os

for t in range(1, 11):
    inputName = "n" + str(t) + ".in"
    outputName = "n" + str(t) + ".test"
    command = "standard.exe < " + inputName + " > " + outputName;
    print(command)
    os.system(command);
