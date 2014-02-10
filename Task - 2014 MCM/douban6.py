import os
import codecs

file = open("list.html", "r")
lines = file.readlines()
file.close()

movieDict = {}
file = codecs.open("movie.dict", "r", "utf-8")
for line in file.readlines():
    words = line.split("~")
    movieDict[words[0]] = words[1][:-1]
file.close()

nameDict = {}
file = codecs.open("name.dict", "r", "utf-8")
for line in file.readlines():
    words = line.split("~")
    nameDict[words[0]] = words[1][:-1]
file.close()

infos = []
for line in lines:
    url = line[:-1]
    id = url[32:-1]
    file_name = "raw/" + id + ".txt"
    if not os.path.exists(file_name):
        continue
    file = codecs.open(file_name, "r", "utf-8")
    info = file.readlines()
    file.close()
    if len(info) < 4:
        continue
    for i in range(len(info)):
        info[i] = info[i][:-1]
    struct = {}
    struct["name"] = movieDict[info[0]]
    struct["score"] = info[1]
    if len(info[2]) == 0:
        print(info[2])
    struct["votes"] = info[2]
    struct["star"] = []
    for star in info[3].split("/"):
        if len(star) > 1:
            struct["star"].append(nameDict[star])
    infos.append(struct)
file = codecs.open("movie.data", "w", "utf-8")
file.write(str(len(infos)) + "\n")
for info in infos:
    file.write(info["name"] + "\n")
    file.write(info["score"] + "\n")
    file.write(info["votes"] + "\n")
    file.write(str(len(info["star"])) + "\n")
    for star in info["star"]:
        file.write(star + "\n")
file.close()