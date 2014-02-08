import re

tag_page = 137
pattern = re.compile(r'http://movie.douban.com/subject/\d+/')
file = open("list.html", "w")
file.close()
for i in range(tag_page):
    file = open("list/list" + str(i) + ".html", "r")
    html = file.read()
    file.close()
    match = re.findall(pattern, html)
    file = open("list.html", "a")
    for site in set(match):
        file.write(site + "\n")
    file.close()