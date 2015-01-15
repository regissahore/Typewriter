# Version 0.15 (2014-12-31)
import codecs
from pyquery import PyQuery
import HTMLParser  

def translate(s):
    s = s.replace('&#8594;', '\t')
    s = s.replace('<span class="space"> </span>', ' ')
    return HTMLParser.HTMLParser().unescape(s)
    
spec = open('spec.html', 'r').read()
d = PyQuery(spec)
total_num = 531
for i in range(0, total_num):
    num = str(i + 1)
    div_name = 'example-' + num
    example_div = d('#' + div_name)
    dd = PyQuery(example_div)
    markdown = str(PyQuery(dd('.language-markdown'))('code'))[32:-8]
    html = str(PyQuery(dd('.language-html'))('code'))[28:-8]
    codecs.open(num + '.in', 'w', 'utf-8').write(translate(markdown))
    codecs.open(num + '.out', 'w', 'utf-8').write(translate(html))
open('case_common', 'w').write('\n'.join(['common/' + str(i + 1) for i in range(0, total_num)]))