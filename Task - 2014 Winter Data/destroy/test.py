import os

for t in range(1, 11):
    inputName = "destroy" + str(t) + ".in"
    outputName = "destroy" + str(t) + ".out"
    command = "python33 brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
