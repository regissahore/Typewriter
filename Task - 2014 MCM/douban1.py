import os
import time
import urllib2

tag_url = 'http://movie.douban.com/tag/%E9%A6%99%E6%B8%AF'
tag_page = 137

for i in range(tag_page):
    file_name = "list/list" + str(i) + ".html"
    if os.path.exists(file_name):
        if os.path.getsize(file_name) > 25600:
            continue
    spe_tag_url = tag_url + "?start=" + str(i * 20) + "&type=T"
    print(spe_tag_url)
    flag = True
    while flag:
        try:
            request = urllib2.Request(spe_tag_url)
            html = urllib2.urlopen(request).read()
            flag = False
        except:
            print("Retry")
    file = open(file_name, "w")
    file.write(html)
    file.close()
    time.sleep(10)