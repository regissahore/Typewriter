import os
import time
import urllib2

file = open("list.html", "r")
lines = file.readlines()
file.close()

for line in lines:
    url = line[:-1]
    id = url[32:-1]
    print(id)
    file_name = "movie/" + id + ".html"
    if os.path.exists(file_name):
        if os.path.getsize(file_name) > 25600:
            continue
    flag = True
    while flag:
        try:
            request = urllib2.Request(url)
            html = urllib2.urlopen(request).read()
            flag = False
        except:
            print("Retry")
    file = open(file_name, "w")
    file.write(html)
    file.close()
    time.sleep(5)