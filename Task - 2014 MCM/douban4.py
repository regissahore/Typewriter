import os
import re
import codecs

file = open("list.html", "r")
lines = file.readlines()
file.close()

patternName = re.compile('<span property="v:itemreviewed">(.*?)</span>')
patternScore = re.compile('<strong class="ll rating_num" property="v:average">(.*?)</strong>')
patternVotes = re.compile('<span property="v:votes">(.*?)</span>')
patternStar = re.compile('rel="v:starring">(.*?)</a>')

for line in lines:
    url = line[:-1]
    id = url[32:-1]
    file_name = "movie/" + id + ".html"
    if not os.path.exists(file_name):
        continue
    file = codecs.open(file_name, "r", "utf-8")
    html = file.read()
    file.close()
    file = codecs.open("raw/" + id + ".txt", "w", "utf-8")
    res = re.search(patternName, html)
    if res != None:
        name = res.group(1).split(" ")[0]
        file.write(name + "\n")
    res = re.search(patternScore, html)
    if res != None:
        file.write(res.group(1) + "\n")
    res = re.search(patternVotes, html)
    if res != None:
        file.write(res.group(1) + "\n")
    stars = re.findall(patternStar, html)
    first = True
    for star in stars:
        if first:
            first = False
        else:
            file.write("/")
        file.write(star)
    if not first:
        file.write("\n")
    file.close()