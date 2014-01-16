import os

for t in range(1, 11):
    inputName = "iq" + str(t) + ".in"
    outputName = "iq" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);
