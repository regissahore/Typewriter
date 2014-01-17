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
    if (header3Count > 0) {
        document.write("</div>");
        header3Count = 0;
    }
    if (header2Count > 0) {
        document.write("</div>");
        header2Count = 0;
    }
    if (header1Count > 0) {
        document.write("</div>");
    }
    ++header1Count;
    document.write("<div id = '" + header1Count + " " + title + "' name = header1>");
    document.write("<div class = header1>");
    document.write("<span class = header1_num>");
    document.write(header1Count + "&nbsp;");
    document.write("</span>");
    document.write("<span class = header1_text>");
    document.write(title);
    document.write("</span>");
    document.write("</div>");
}

function header2(title) {
    if (header3Count > 0) {
        document.write("</div>");
        header3Count = 0;
    }
    if (header2Count > 0) {
        document.write("</div>");
    }
    ++header2Count;
    title = header1Count + "." + header2Count + " " + title;
    document.write("<div id = '" + title + "' name = header2>");
    document.write("<div class = header2>");
    document.write(title);
    document.write("</div>");
}

function header3(title) {
    if (header3Count > 0) {
        document.write("</div>");
    }
    ++header3Count;
    title = header1Count + "." + header2Count + "." + header3Count + " " + title;
    document.write("<div id = '" + title + "' name = header3>");
    document.write("<div class = header3>");
    document.write(title);
    document.write("</div>");
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
    var isComment = false;
    var lastString = "";
    var stringStart = "";
    var lastCh = '';
    for (var i = 0; i < script.length; ++i) {
        if (isComment) {
            lastString += script[i];
        } else if (isString) {
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
            } else if (script[i] == '/' && (i + 1 < script.length && script[i + 1] == '/' && i + 1 < script.length)) {
                isComment = true;
            } else {
                writeCharacter(script[i]);
                lastString = "";
            }
        }
        lastCh = script[i];
    }
    if (isComment) {
        document.write("<span class = code_comment>");
        writeCharacter(lastString);
        document.write("</span>");
    }
    document.write("<br/>");
}

function printScript(script) {
    document.write("<fieldset class = code_field>");
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
    document.write("<fieldset class = code_field>");
    document.write("<legend>" + "运行结果" + "</legend>");
    var code = "";
    for (var i = 0; i < script.length; ++i) {
        code += script[i] + "\n";
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

function addIndexDiv() {
    document.write("<div id = compose_index></div>");
}

function createIndexLink(name) {
    var link = document.createElement('a');
    link.href = "#" + name;
    link.innerText = name;
    return link;
}

function addIndex() {
    var indexDiv = document.getElementById('compose_index');
    var indexTitle = document.createElement('div');
    indexTitle.className = 'index_title';
    indexTitle.innerText = '目录';
    indexDiv.appendChild(indexTitle);
    var header1 = document.getElementsByName('header1');
    var header2 = document.getElementsByName('header2');
    var header3 = document.getElementsByName('header3');
    for (var i = 0; i < header1.length; ++i) {
        var header1Div = document.createElement('div');
        header1Div.className = 'index_header1';
        header1Div.appendChild(createIndexLink(header1[i].id));
        indexDiv.appendChild(header1Div);
        for (var j = 0; j < header2.length; ++j) {
            if (header2[j].id.split('.')[0] != header1[i].id.split(' ')[0]) {
                continue;
            }
            var header2Div = document.createElement('div');
            header2Div.className = 'index_header2';
            header2Div.appendChild(createIndexLink(header2[j].id));
            header1Div.appendChild(header2Div);
            for (var k = 0; k < header3.length; ++k) {
                if (header3[k].id.split('.')[0] != header2[j].id.split('.')[0] ||
                    header3[k].id.split('.')[1] != header2[j].id.split('.')[1].split(' ')[0]) {
                    continue;
                }
                var header3Div = document.createElement('div');
                header3Div.className = 'index_header3';
                header3Div.appendChild(createIndexLink(header3[k].id));
                header2Div.appendChild(header3Div);
            }
        }
    }
}

addIndexDiv();
