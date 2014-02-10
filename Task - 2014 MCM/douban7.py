import codecs

nameDict = {}
file = codecs.open("name.dict", "r", "utf-8")
for line in file.readlines():
    words = line.split("~")
    nameDict[words[1][:-1]] = words[0]
file.close()

file = codecs.open("out.txt", "r", "utf-8")
lines = file.readlines()
file.close()

file = codecs.open("top.txt", "w", "utf-8")
for line in lines:
    word = line.split(" ")
    file.write(nameDict[word[0]] + "\r\n")
file.close()