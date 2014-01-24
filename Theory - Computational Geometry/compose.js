/**
 * 高亮显示C++。
 * @author ZHG <CyberZHG@gmail.com>
 */

keywords = ["asm", "default", "float", "operator", "static_cast", "union", "auto", "delete", "for", "private", "struct", "unsigned", "bool", "do", "friend", "protected", "switch", "using", "break", "double", "goto", "public", "template", "virtual", "case", "dynamic_cast", "if", "register", "this", "void", "catch", "else", "inline", "reinterpret_cast", "throw", "volatile", "char", "enum", "int", "return", "true", "wchar_t", "class", "explicit", "long", "short", "try", "while", "const", "export", "mutable", "signed", "typedef", "const_cast", "extern", "namespace", "sizeof", "typeid", "continue", "false", "new", "static", "typename"];
systems = ["Point", "Segment", "Line", "Rectangle", "Triangle", "Polygon", "Circle"];

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
    var res = "";
    for (var i = 0; i < script.length; ++i) {
        if (script[i] == ' ') {
            res += "&nbsp;";
        } else if (script[i] == '<') {
            res += "&lt;";
        } else if (script[i] == '>') {
           res += "&gt;";
        } else if (script[i] == '\t') {
            res += "&emsp;";
        } else {
            res += script[i];
        }
    }
    return res;
}

function writeScript(script) {
    var res = "";
    if (script[0] == '#') {
        res += "<span class = code_marco>";
        res += writeCharacter(script);
        res += "</span>";
        return res;
    }
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
                res += "<span class = code_string>";
                res += writeCharacter(lastString);
                res += "</span>";
                lastString = "";
                isString = false;
            }
        } else if (isNum) {
            if (script[i] == '.' || isDigit(script[i]) || (script[i] >= 'a' && script[i] <= 'f') || (script[i] >= 'A' && script[i] <= 'F')) {
                lastString += script[i];
            } else {
                res += "<span class = code_number>";
                res += writeCharacter(lastString);
                res += "</span>";
                lastString = "";
                isNum = false;
                --i;
            }
        } else if (isWord) {
            if (isCharacter(script[i])) {
                lastString += script[i];
            } else if (isDigit(script[i]) || script[i] == '_') {
                res += writeCharacter(lastString);
                lastString = "";
                isWord = false;
                --i;
            } else {
                var flag = true;
                for (var j = 0; j < keywords.length; ++j) {
                    if (keywords[j] == lastString) {
                        flag = false;
                        res += "<span class = code_keyword>";
                        res += writeCharacter(lastString);
                        res += "</span>";
                        break;
                    }
                }
                for (var j = 0; j < systems.length; ++j) {
                    if (systems[j] == lastString) {
                        flag = false;
                        res += "<span class = code_system>";
                        res += writeCharacter(lastString);
                        res += "</span>";
                        break;
                    }
                }
                if (flag) {
                    res += writeCharacter(lastString);
                }
                lastString = "";
                isWord = false;
                --i;

            }
        } else {
            lastString += script[i];
            if (!isCharacter(lastCh) && isDigit(script[i])) {
                isNum = true;
            } else if (!isCharacter(lastCh) && isCharacter(script[i])) {
                isWord = true;
            } else if (script[i] == '"' || script[i] == "'") {
                isString = true;
                stringStart = script[i];
            } else if (script[i] == '/' && (i + 1 < script.length && script[i + 1] == '/' && i + 1 < script.length)) {
                isComment = true;
            } else {
                res += writeCharacter(script[i]);
                lastString = "";
            }
        }
        lastCh = script[i];
    }
    if (isComment) {
        res += "<span class = code_comment>";
        res += writeCharacter(lastString);
        res += "</span>";
    }
    res += "<br/>";
    return res;
}

function printScript(script) {
    var res = "";
    script = script.split('\n');
    res += "<table cellspacing = 0>";
    for (var i = 0; i < script.length; ++i) {
        res += "<tr><td class = table_line >" + (i + 1) + "</td>";
        res += "<td class = table_code>";
        res += writeScript(script[i]);
        res += "</td></tr>";
    }
    res += "</table>";
    return res;
}
