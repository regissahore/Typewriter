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
