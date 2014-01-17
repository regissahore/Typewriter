/**
 * 网页排版，标题的自动编号与高亮显示JavaScript脚本。
 * @author ZHG <CyberZHG@gmail.com>
 */

keywords = ["break", "case", "catch", "continue", "default", "delete", "do", "else", "finally", "for", "function", "if", "in", "instanceof", "new", "return", "switch", "this", "throw", "try", "typeof", "var", "void", "while", "with", "abstract", "boolean", "byte", "char", "class", "const", "debugger", "double", "enum", "export", "extends", "final", "float", "goto", "implements", "import", "int", "interface", "long", "native", "package", "private", "protected", "public", "short", "static", "super", "synchronized", "throws", "transient", "volatile"];
systems = ["document", "eval"];

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

function isDigit(str) {
    return str >= '0' && str <= '9';
}

function isLower(str) {
    return str >= 'a' && str <= 'z';
}

function isUpper(str) {
    return str >= 'A' && str <= 'Z';
}

function isCharacter(str) {
    return isLower(str) || isUpper(str);
}

function writeCharacter(script) {
    for (var i = 0; i < script.length; ++i) {
        if (script[i] == ' ') {
            document.write("&nbsp;");
        } else if (script[i] == '<') {
            document.write("&lt;");
        } else if (script[i] == '>') {
            document.write("&gt;");
        } else if (script[i] == '\t') {
            document.write("&emsp;");
        } else {
            document.write(script[i]);
        }
    }
}

function writeScript(script) {
    var isNum = false;
    var isWord = false;
    var isString = false;
    var lastString = "";
    var stringStart = "";
    var lastCh = '';
    for (var i = 0; i < script.length; ++i) {
        if (isString) {
            lastString += script[i];
            if (lastCh != '\\' && script[i] == stringStart) {
                document.write("<span class = code_string>");
                writeCharacter(lastString);
                document.write("</span>");
                lastString = "";
                isString = false;
            }
        } else if (isNum) {
            if (script[i] == '.' || isDigit(script[i]) || (script[i] >= 'a' && script[i] <= 'f') || (script[i] >= 'A' && script[i] <= 'F')) {
                lastString += script[i];
            } else {
                document.write("<span class = code_number>");
                writeCharacter(lastString);
                document.write("</span>");
                lastString = "";
                isNum = false;
                --i;
            }
        } else if (isWord) {
            if (isLower(script[i])) {
                lastString += script[i];
            } else if (isUpper(script[i]) || isDigit(script[i]) || script[i] == '_') {
                writeCharacter(lastString);
                lastString = "";
                isWord = false;
                --i;
            } else {
                var flag = true;
                for (var j = 0; j < keywords.length; ++j) {
                    if (keywords[j] == lastString) {
                        flag = false;
                        document.write("<span class = code_keyword>");
                        writeCharacter(lastString);
                        document.write("</span>");
                        break;
                    }
                }
                for (var j = 0; j < systems.length; ++j) {
                    if (systems[j] == lastString) {
                        flag = false;
                        document.write("<span class = code_system>");
                        writeCharacter(lastString);
                        document.write("</span>");
                        break;
                    }
                }
                if (flag) {
                    writeCharacter(lastString);
                }
                lastString = "";
                isWord = false;
                --i;

            }
        } else {
            lastString += script[i];
            if (!isCharacter(lastCh) && isDigit(script[i])) {
                isNum = true;
            } else if (!isCharacter(lastCh) && script[i] >= 'a' && script[i] <= 'z') {
                isWord = true;
            } else if (script[i] == '"' || script[i] == "'") {
                isString = true;
                stringStart = script[i];
            } else {
                writeCharacter(script[i]);
                lastString = "";
            }
        }
        lastCh = script[i];
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
    var code = "";
    for (var i = 0; i < script.length; ++i) {
        code += script[i];
    }
    eval(code);
    document.write("</fieldset>");
}

function showScript(script) {
    printScript(script);
    document.write("<br/>");
    runScript(script);
    document.write("<br/>");
}
