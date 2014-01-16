keywords = ["break", "case", "catch", "continue", "default", "delete", "do", "else", "finally", "for", "function", "if", "in", "instanceof", "new", "return", "switch", "this", "throw", "try", "typeof", "var", "void", "while", "with", "abstract", "boolean", "byte", "char", "class", "const", "debugger", "double", "enum", "export", "extends", "final", "float", "goto", "implements", "import", "int", "interface", "long", "native", "package", "private", "protected", "public", "short", "static", "super", "synchronized", "throws", "transient", "volatile"];

var header1Count = 0;
var header2Count = 0;
var header3Count = 0;
function header1(title) {
    ++header1Count;
    header2Count = 0;
    header3Count = 0;
    document.write("<h1>" + header1Count + "." + title + "</h1>");
}

function header2(title) {
    ++header2Count;
    header3Count = 0;
    document.write("<h2>" + header1Count + "." + header2Count + " " + title + "</h2>");
}

function header3(title) {
    ++header3Count;
    document.write("<h3>" + header1Count + "." + header2Count + "." + header3Count + " " + title + "</h3>");
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

function writeScript(script) {
    var isNum = false;
    var isWord = false;
    var isString = false;
    var lastString = "";
    var stringStart = "";
    for (var i = 0; i < script.length; ++i) {
        if (isString) {
            lastString += script[i];
            if (script[i] == stringStart) {
                document.write("<span class = code_string>");
                document.write(lastString);
                document.write("</span>");
                lastString = "";
                isString = false;
            }
        } else if (isNum) {
            if (script[i] == '.' || (script[i] >= '0' && script[i] <= '9') || (script[i] >= 'a' && script[i] <= 'f') || (script[i] >= 'A' && script[i] <= 'F')) {
                lastString += script[i];
            } else {
                document.write("<span class = code_number>");
                document.write(lastString);
                document.write("</span>");
                lastString = "";
                isNum = false;
                --i;
            }
        } else if (isWord) {
            if (script[i] >= 'a' && script[i] <= 'z') {
                lastString += script[i];
            } else if ((script[i] >= 'A' && script[i] <= 'Z') || (script[i] >= '0' && script[i] <= '9') || script[i] == '_') {
                document.write(lastString);
                lastString = "";
                isWord = false;
                --i;
            } else {
                var flag = true;
                for (var j = 0; j < keywords.length; ++j) {
                    if (keywords[j] == lastString) {
                        flag = false;
                        document.write("<span class = code_keyword>");
                        document.write(lastString);
                        document.write("</span>");
                        break;
                    }
                }
                if (flag) {
                    document.write(lastString);
                }
                lastString = "";
                isWord = false;
                --i;

            }
        } else {
            lastString += script[i];
            if (script[i] >= '0' && script[i] <= '9') {
                isNum = true;
            } else if (script[i] >= 'a' && script[i] <= 'z') {
                isWord = true;
            } else if (script[i] == '"' || script[i] == "'") {
                isString = true;
                stringStart = script[i];
            } else {
                document.write(script[i]);
                lastString = "";
            }
        }
    }
    document.write("<br/>");
}

function printScript(script) {
    document.write("<fieldset>");
    document.write("<legend>" + "代码" + "</legend>");
    document.write("<table cellspacing = 0>");
    for (var i = 0; i < script.length; ++i) {
        document.write("<tr><td class = table_line >" + (i + 1) + "</td>");
        if (i % 2 == 0) {
            document.write("<td class = table_code_even>");
        } else {
            document.write("<td class = table_code_odd>");
        }
        writeScript(script[i]);
        document.write("</td></tr>");
    }
    document.write("</table>");
    document.write("</fieldset>");
}

function runScript(script) {
    document.write("<fieldset>");
    document.write("<legend>" + "运行结果" + "</legend>");
    document.write("<table cellspacing = 0>");
    for (var i = 0; i < script.length; ++i) {
        document.write("<tr><td class = table_line >" + (i + 1) + "</td>");
        if (i % 2 == 0) {
            document.write("<td class = table_code_even>");
        } else {
            document.write("<td class = table_code_odd>");
        }
        eval(script[i]);
        document.write("</td></tr>");
    }
    document.write("</table>");
    document.write("</fieldset>");
}

function showScript(script) {
    printScript(script);
    document.write("<br/>");
    runScript(script);
}

// 从这里正文开始

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
    "writeLine(boolVariable);",
    "writeLine(numberVariable);",
    "writeLine(stringVariable);"
]);
