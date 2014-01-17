header1("变量类型");
header2("基本类型");
list([
    "基本类型有三种，分别为布尔、数字和字符串。",
    "在JavaScript中不区分小数和整数。"
]);
showScript([
    "var boolVariable = true;",
    "var numberVariable = 1.23;",
    "var stringVariable = \"string\" + boolVariable + numberVariable;",
    "document.write(boolVariable + '<br/>');",
    "document.write(numberVariable + '<br/>');",
    "document.write(stringVariable + '<br/>');"
]);
header2("字符串");
header3("声明");
list([
    "JavaScript支持用''或\"\"声明字符串。",
    "在一种引号间出现另外一种引号不需转义就可以正常使用。",
    "两种字符串没有本质上的区别。"
]);
showScript([
    "var str1 = \"在\\\"双引号\\\"中使用'单引号'的字符串。\";",
    "var str2 = '在\\\'单引号\\\'中使用\"双引号\"的字符串。';",
    "document.write(str1 + '<br/>');",
    "document.write(str2 + '<br/>');"
]);
header3("长度");
list([
    "JavaScript中，不同字符的长度均为1。"
]);
showScript([
    "var str1 = 'Yang';",
    "var str2 = '杨教授';",
    "document.write(str1.length + '<br/>');",
    "document.write(str2.length + '<br/>');"
]);
header3("返回子串");
list([
    "用substr返回子串，参数为起始位置和字符个数。"
]);
showScript([
    "var str = 'Professor Yang';",
    "document.write(str.substr(3, 5) + '<br/>');"
]);
header3("寻找子串");
list([
    "可以用indexOf来寻找子串第一次出现的位置。",
    "如果没找到返回-1。"
]);
showScript([
    "var str = 'Professor Yang';",
    "if (str.indexOf('hentai') == -1) {",
    "    document.write(str + ' is Hentai! ' + '<br/>');",
    "}"
]);
header3("字符串匹配");
list([
    "利用match可以用来做正则表达式的匹配。",
    "如果成功返回匹配的字符串。"
]);
showScript([
    "var str = 'CyberZHG@gmail.com';",
    "var reg = /^([a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+((\.[a-zA-Z0-9_-]{2,3}){1,2})$/;",
    "document.write(str.match('ZHG') + '<br/>');",
    "document.write(str.match('Yang') + '<br/>');",
    "document.write(str.match(reg) + '<br/>');"
]);
header3("字符串效果");
list([
    "这一部分主要用于网页上的显示。",
]);
showScript([
    "var str = '杨教授 is Hentai。';",
    "document.write(str.big() + '<br/>');",
    "document.write(str.small() + '<br/>');",
    "document.write(str.bold() + '<br/>');",
    "document.write(str.italics() + '<br/>');",
    "document.write(str.blink() + '<br/>');",
    "document.write(str.fixed() + '<br/>');",
    "document.write(str.strike() + '<br/>');",
    "document.write(str.fontcolor('Red') + '<br/>');",
    "document.write(str.fontsize(16) + '<br/>');",
    "document.write(str.toLowerCase() + '<br/>');",
    "document.write(str.toUpperCase() + '<br/>');",
    "document.write(str.sub() + '<br/>');",
    "document.write(str.sup() + '<br/>');",
    "document.write(str.link('https://github.com/CyberZHG/') + '<br/>');"
]);
header2("数组");
header3("初始化");
showScript([
    "var array1 = new Array();",
    "var array2 = new Array('test', true, 3);",
    "var array3 = [1, false, 'what'];",
    "for (var i = 0; i < array3.length; ++i) {",
    "    document.write(array3[i] + '<br/>');",
    "}"
]);
header2("对象");
header2("Json");
header2("Undefined和Null");
