import os

for t in range(1, 11):
    inputName = "function2" + str(t) + ".in"
    outputName = "function2" + str(t) + ".out"
    command = "brute.py < " + inputName + " > " + outputName
    print(command)
    os.system(command);
