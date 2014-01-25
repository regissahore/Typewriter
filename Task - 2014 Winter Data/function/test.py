import os

for t in range(1, 11):
    inputName = "function" + str(t) + ".in"
    outputName = "function" + str(t) + ".test"
    command = "standard.exe < " + inputName + " > " + outputName;
    print(command)
    os.system(command);
