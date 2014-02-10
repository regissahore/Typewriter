import os
import time
import urllib2

file = open("list.html", "r")
lines = file.readlines()
file.close()
count = 0

for line in lines:
    url = line[:-1]
    id = url[32:-1]
    file_name = "movie/" + id + ".html"
    count = count + 1
    if os.path.exists(file_name):
        if os.path.getsize(file_name) > 25600:
            continue
    print(str(count) + " " + id)
    flag = True
    retry = 0
    while flag:
        try:
            request = urllib2.Request(url)
            html = urllib2.urlopen(request).read()
            flag = False
            file = open(file_name, "w")
            file.write(html)
            file.close()
            time.sleep(2)
        except:
            retry = retry + 1
            print("Retry " + str(retry))