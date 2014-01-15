function header1(title) {
    document.write("<h1>" + title + "</h1>");
}

function header2(title) {
    document.write("<h2>" + title + "</h2>");
}

function header3(title) {
    document.write("<h3>" + title + "</h3>");
}

function list(lists) {
    document.write("<ul>");
    for (var i = 0; i < lists.length; ++i) {
        document.write("<li>" + lists[i] + "</li>");
    }
    document.write("</ul>");
}

function writeLine(obj) {
    document.write(obj);
    document.write("<br/>");
}

function printScript(script) {
    document.write("<fieldset>");
    document.write("<legend>" + "代码" + "</legend>");
    for (var i = 0; i < script.length; ++i) {
        writeLine(script[i]);
    }
    document.write("</fieldset>");
}

function runScript(script) {
    document.write("<fieldset>");
    document.write("<legend>" + "运行结果" + "</legend>");
    for (var i = 0; i < script.length; ++i) {
        eval(script[i]);
    }
    document.write("</fieldset>");
}

function showScript(script) {
    printScript(script);
    runScript(script);
}

header1("变量类型");
list([
    "基本类型有三种，分别为布尔、数字和字符串。",
    "在JavaScript中不区分小数和整数。"
]);
showScript([
    "var boolVariable = true;",
    "var numberVariable = 1.23;",
    "var stringVariable = \"string\" + boolVariable + numberVariable;",
    "writeLine(boolVariable);",
    "writeLine(numberVariable);",
    "writeLine(stringVariable);"
]);
