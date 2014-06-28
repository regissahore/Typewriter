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
    return symbol;
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
    cout << "DATA ENDS" << endl;
    cout << "CODE SEGMENT" << endl;
    cout << "\tASSUME CS:CODE" << endl;
    cout << "START:" << endl;
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
            cout << "\tJA " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "<") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJB " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == ">=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJAE " << label << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 0" << endl;
            cout << label << ":" << endl;
        } else if (op == "<=") {
            cout << "\tMOV AX, " << quats[i].symbol1 << endl;
            cout << "\tCMP AX, " << quats[i].symbol2 << endl;
            cout << "\tMOV " << quats[i].symbol3 << ", 1" << endl;
            string label = getBoolLabel(i);
            cout << "\tJBE " << label << endl;
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
        }
    }
    for (auto label : labelTable) {
        if (label.value == (int)quats.size()) {
            cout << label.symbol << ":" << endl;
        }
    }
    cout << "\tINT 21H" << endl;
    cout << "\tRET" << endl;
    cout << "CODE ENDS" << endl;
    cout << "END START" << endl;
}
