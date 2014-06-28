#include <cstdio>
#include <iostream>
#include "asm.h"
using namespace std;

string getBoolLabel(int pos) {
    char num[12];
    sprintf(num, "BOOL_%d", pos);
    return string(num);
}

string getNewName(string symbol) {
    if (symbol[0] == '$') {
        return "temp_" + symbol.substr(1);
    }
    if (symbol[0] == '%') {
        return "const_" + symbol.substr(1);
    }
    if (symbol[0] == '#') {
        return "LABEL_" + symbol.substr(1);
    }
    return "var_" + symbol;
}

void printAssembly(vector<Quaternion> &quats,
                   map<string, int> &symbolMap,
                   vector<SymbolNode> &symbolTable,
                   map<string, int> &labelMap,
                   vector<SymbolNode> &labelTable) {
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        SymbolNode &node = symbolTable[i];
        string oldName = node.symbol;
        node.symbol = getNewName(oldName);
        symbolMap[node.symbol] = symbolMap[oldName];
    }
    for (size_t i = 0; i < labelTable.size(); ++i) {
        SymbolNode &node = labelTable[i];
        string oldName = node.symbol;
        node.symbol = getNewName(oldName);
        symbolMap[node.symbol] = symbolMap[oldName];
    }
    for (size_t i = 0; i < quats.size(); ++i) {
        Quaternion &quat = quats[i];
        quat.symbol1 = getNewName(quat.symbol1);
        quat.symbol2 = getNewName(quat.symbol2);
        quat.symbol3 = getNewName(quat.symbol3);
    }
    cout << "DATA SEGMENT" << endl;
    for (auto node : symbolTable) {
        cout << "\t" << node.symbol;
        cout << "\tDW\t" << node.value << endl;
    }
    cout << "\tINPUT_BUFFER DB 128 DUP(0)" << endl;
    cout << "DATA ENDS" << endl;
    bool hasRead = false, hasWrite = false;
    cout << "CODE SEGMENT" << endl;
    cout << "\tASSUME CS: CODE, DS: DATA" << endl;
    cout << "START:" << endl;
    cout << "\tMOV AX, DATA" << endl;
    cout << "\tMOV DS, AX" << endl;
    for (size_t i = 0; i < quats.size(); ++i) {
        for (auto label : labelTable) {
            if (label.value == (int)i) {
                cout << label.symbol << ":" << endl;
            }
        }
        string &op = quats[i].op;
        if (op == "+") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tADD AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", AX" << endl;
        } else if (op == "-") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tSUB AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", AX" << endl;
        } else if (op == "*") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tMUL " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", AX" << endl;
        } else if (op == "/") {
            cout << "\tMOV DX, 0" << endl;
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tDIV " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", AX" << endl;
        } else if (op == "&") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tAND AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", AX" << endl;
        } else if (op == "|") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tOR AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV" << quats[i].symbol3 << endl;
        } else if (op == "=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tMOV " <<quats[i].symbol3 << ", AX" << endl;
        } else if (op == ">") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJG " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "<") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJL " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == ">=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJGE " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "<=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJLE " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "==") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJE " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "!=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJNE " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "JZ") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tAND AX, AX" << endl;
            cout << "\tJZ " << quats[i].symbol3 << endl;
        } else if (op == "JP") {
            cout << "\tJMP " << quats[i].symbol3 << endl;
        } else if (op == "READ") {
            hasRead = true;
            cout << "\tCALL READ_INT" << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", BX" << endl;
        } else if (op == "WRITE") {
            hasWrite = true;
            cout << "\tMOV BX, " << quats[i].symbol1 << endl;
            cout << "\tCALL WRITE_INT" << endl;
        }
    }
    for (auto label : labelTable) {
        if (label.value == (int)quats.size()) {
            cout << label.symbol << ":" << endl;
        }
    }
    cout << "\tMOV AX, 4C00H" << endl;
    cout << "\tINT 21H" << endl;
    if (hasRead) {
        FILE *file = fopen("read_int.asm", "r");
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    }
    if (hasWrite) {
        FILE *file = fopen("write_int.asm", "r");
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    }
    if (hasRead || hasWrite) {
        FILE *file = fopen("write_newline.asm", "r");
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    }
    cout << "CODE ENDS" << endl;
    cout << "END START" << endl;
}
