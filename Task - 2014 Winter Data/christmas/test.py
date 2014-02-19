import os

for t in range(1, 11):
    inputName = "christmas" + str(t) + ".in"
    outputName = "christmas" + str(t) + ".out"
    command = "standard.exe < " + inputName + " > " + outputName
    print(command)
    os.system(command);


for t in range(1, 11):
    inputName = "christmas" + str(t) + ".in"
    outputName = "christmas" + str(t) + ".test"
    command = "python33 brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
