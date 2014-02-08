#coding=utf-8
import os
import codecs
from pinyin import PinYin

file = open("list.html", "r")
lines = file.readlines()
file.close()

def lowerPinyin(word):
    res = ""
    for ch in word.capitalize():
        if ch >= 'a' and ch <= 'z':
            res += ch
        if ch >= 'A' and ch <= 'Z':
            res += ch
    return res

pinyinDict = {}
file = open("word.data", "r")
pinyins = file.readlines()
for pinyin in pinyins:
    words = pinyin.split(" ")
    if len(words[1]) == 0:
        pinyinDict[words[0]] = lowerPinyin(words[2])
    else:
        pinyinDict[words[0]] = lowerPinyin(words[1])
file.close()

def getPinyin(name):
    res = ""
    global pin
    for ch in name:
        key = '%X' % ord(ch)
        if pinyinDict.has_key(key):
            res += pinyinDict[key]
        elif ch == u"：":
            res += ":"
        elif ch == u"·":
            res += "."
        elif ch == u"Ⅰ":
            res += "1"
        elif ch == u"Ⅱ":
            res += "2"
        elif ch == u"Ⅲ":
            res += "3"
        elif ch == u"Ⅳ":
            res += "4"
        elif ch == u"Ⅴ":
            res += "5"
        elif ch == u"Ⅵ":
            res += "6"
        elif ch == u"Ⅶ":
            res += "7"
        elif ch == u"（":
            res += "("
        elif ch == u"）":
            res += ")"
        elif ch == "~":
            res += "-"
        else:
            res += ch
    return res

movieDict = {}
nameDict = {}
    
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
    movieDict[info[0][:-1]] = getPinyin(info[0][:-1])
    stars = info[3].split("/")
    for star in stars:
        if len(star) == 0:
            continue
        if star[-1] == "\n":
            star = star[:-1]
        nameDict[star] = getPinyin(star)
        
file = codecs.open("movie.dict", "w", "utf-8")
for (key, value) in movieDict.items():
    file.write(key + "~" + value + "\n")
file.close()

file = codecs.open("name.dict", "w", "utf-8")
for (key, value) in nameDict.items():
    file.write(key + "~" + value + "\n")
file.close()