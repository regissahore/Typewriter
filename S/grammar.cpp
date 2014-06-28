#include <map>
#include <cstdio>
#include <iostream>
#include "grammar.h"
using namespace std;

int constIndex;
int tempSymbolIndex;
vector<SymbolNode> symbolTable;
map<string, int> symbolMap;
int labelIndex;
vector<SymbolNode> labelTable;
map<string, int> labelMap;

void addSymbol(string &symbol) {
    symbolMap[symbol] = symbolTable.size();
    symbolTable.push_back({symbol, 0});
}

bool isSymbolExist(string &symbol) {
    return symbolMap.find(symbol) != symbolMap.end();
}

int getSymbol(string &symbol) {
    return symbolMap[symbol];
}

string addTempSymbol() {
    char num[12];
    sprintf(num, "$%d", ++tempSymbolIndex);
    string symbol(num);
    if (!isSymbolExist(symbol)) {
        addSymbol(symbol);
    }
    return symbol;
}

string addLabel() {
    char num[12];
    sprintf(num, "#%d", ++labelIndex);
    string label(num);
    labelMap[label] = labelTable.size();
    labelTable.push_back({label, 0});
    return label;
}

void setLabel(string &label, int value) {
    labelTable[labelMap[label]].value = value;
}

int getLabel(string &label) {
    return labelTable[labelMap[label]].value;
}

string addConst(int value) {
    char num[12];
    sprintf(num, "%%%d", ++constIndex);
    string symbol(num);
    addSymbol(symbol);
    symbolTable[getSymbol(symbol)].value = value;
    return symbol;
}

void addQuaternion(vector<Quaternion> &quats, string op, string symbol1, string symbol2, string symbol3) {
    int addr1 = 0, addr2 = 0, addr3 = 0;
    if (symbol1.size() > 0) {
        addr1 = getSymbol(symbol1);
    }
    if (symbol2.size() > 0) {
        addr2 = getSymbol(symbol2);
    }
    if (symbol3.size() > 0) {
        addr3 = getSymbol(symbol3);
    }
    quats.push_back({op, symbol1, symbol2, symbol3, addr1, addr2, addr3});
}

void P(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void D(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void S(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void L(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void L_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string B(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string T_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string F_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string E(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string T(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
string F(vector<Quaternion> &quats, vector<Token> &tokens, int &index);

void P(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    if (tokens[index].type == TYPE_L_BRACKET) {
        ++index;
        D(quats, tokens, index);
        S(quats, tokens, index);
    } else {
        cerr << "Program should start with '{'." << endl;
    }
}

void D(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    while (tokens[index].type == TYPE_INT) {
        ++index;
        if (tokens[index].type == TYPE_ID) {
            addSymbol(tokens[index].token);
            ++index;
            if (tokens[index].type == TYPE_SEMICOLON) {
                ++index;
            } else {
                cerr << "Declaration should end up with semicolon." << endl;
            }
        } else {
            cerr << "Declaration should have identifier." << endl;
        }
    }
}

void S(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    if (tokens[index].type == TYPE_IF) {
        ++index;
        if (tokens[index].type == TYPE_L_PARENTHESE) {
            ++index;
            tempSymbolIndex = 0;
            string condition = B(quats, tokens, index);
            if (tokens[index].type == TYPE_R_PARENTHESE) {
                ++index;
                if (tokens[index].type == TYPE_THEN) {
                    ++index;
                    string label1 = addLabel();
                    int pos1 = quats.size();
                    addQuaternion(quats, "JZ", condition, "", label1);
                    S(quats, tokens, index);
                    string label2 = addLabel();
                    int pos2 = quats.size();
                    addQuaternion(quats, "JP", "", "", label2);
                    setLabel(label1, quats.size());
                    quats[pos1].addr3 = quats.size();
                    if (tokens[index].type == TYPE_ELSE) {
                        ++index;
                        S(quats, tokens, index);
                    }
                    setLabel(label2, quats.size());
                    quats[pos2].addr3 = quats.size();
                } else {
                    cerr << "'if' should be followed by 'then'." << endl;
                }
            } else {
                cerr << "The parentheses are mismatched." << endl;
            }
        } else {
            cerr << "The expression should be surrounded by parentheses." << endl;
        }
    } else if (tokens[index].type == TYPE_WHILE) {
        ++index;
        string label1 = addLabel();
        setLabel(label1, quats.size());
        if (tokens[index].type == TYPE_L_PARENTHESE) {
            ++index;
            tempSymbolIndex = 0;
            string condition = B(quats, tokens, index);
            if (tokens[index].type == TYPE_R_PARENTHESE) {
                ++index;
                string label2 = addLabel();
                int pos2 = quats.size();
                addQuaternion(quats, "JZ", condition, "", label2);
                if (tokens[index].type == TYPE_DO) {
                    ++index;
                    S(quats, tokens, index);
                    int pos1 = quats.size();
                    addQuaternion(quats, "JP", condition, "", label1);
                    quats[pos1].addr3 = getLabel(label1);
                    setLabel(label2, quats.size());
                    quats[pos2].addr3 = quats.size();
                } else {
                    cerr << "'while' should be followed by 'do'." << endl;
                }
            } else {
                cerr << "The parentheses are mismatched." << endl;
            }
        } else {
            cerr << "The expression should be surrounded by parentheses." << endl;
        }
    } else if (tokens[index].type == TYPE_L_BRACKET) {
        ++index;
        L(quats, tokens, index);
        if (tokens[index].type == TYPE_R_BRACKET) {
            ++index;
        } else {
            cout << index << endl;
            cerr << "The brackets are mismatched." << endl;
        }
    } else if (tokens[index].type == TYPE_ID) {
        string symbol1 = tokens[index].token;
        ++index;
        if (tokens[index].type == TYPE_ASSIGN) {
            ++index;
            tempSymbolIndex = 0;
            string symbol2 = E(quats, tokens, index);
            addQuaternion(quats, "=", symbol2, "", symbol1);
        } else {
            cerr << "Should be assignment." << endl;
        }
    } else {
        cerr << "Invalid statement." << endl;
    }
}

void L(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    S(quats, tokens, index);
    L_(quats, tokens, index);
}

void L_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    if (tokens[index].type == TYPE_SEMICOLON) {
        ++index;
        L(quats, tokens, index);
    }
}

string B(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    string symbol1 = T_(quats, tokens, index);
    if (tokens[index].type == TYPE_OR) {
        ++index;
        string symbol2 = T_(quats, tokens, index);
        string symbol3 = addTempSymbol();
        addQuaternion(quats, "|", symbol1, symbol2, symbol3);
        return symbol3;
    }
    return symbol1;
}

string T_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    string symbol1 = F_(quats, tokens, index);
    if (tokens[index].type == TYPE_AND) {
        ++index;
        string symbol2 = F_(quats, tokens, index);
        string symbol3 = addTempSymbol();
        addQuaternion(quats, "&", symbol1, symbol2, symbol3);
        return symbol3;
    }
    return symbol1;
}

string F_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    string symbol1 = F(quats, tokens, index);
    if (tokens[index].type == TYPE_RELOP) {
        string relop = tokens[index].token;
        ++index;
        string symbol2 = F(quats, tokens, index);
        string symbol3 = addTempSymbol();
        addQuaternion(quats, relop, symbol1, symbol2, symbol3);
        return symbol3;
    }
    return symbol1;
}

string E(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    string symbol1 = T(quats, tokens, index);
    if (tokens[index].type == TYPE_ADD || tokens[index].type == TYPE_SUB) {
        string op = tokens[index].mnemonic;
        ++index;
        string symbol2 = T(quats, tokens, index);
        string symbol3 = addTempSymbol();
        addQuaternion(quats, op, symbol1, symbol2, symbol3);
        return symbol3;
    }
    return symbol1;
}

string T(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    string symbol1 = F(quats, tokens, index);
    if (tokens[index].type == TYPE_MUL || tokens[index].type == TYPE_DIV) {
        string op = tokens[index].mnemonic;
        ++index;
        string symbol2 = F(quats, tokens, index);
        string symbol3 = addTempSymbol();
        addQuaternion(quats, op, symbol1, symbol2, symbol3);
        return symbol3;
    }
    return symbol1;
}

string F(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    if (tokens[index].type == TYPE_L_PARENTHESE) {
        ++index;
        string symbol = E(quats, tokens, index);
        if (tokens[index].type == TYPE_R_PARENTHESE) {
            ++index;
        } else {
            cerr << "The parentheses are mismatched." << endl;
        }
        return symbol;
    }
    if (tokens[index].type == TYPE_CONST) {
        int constant;
        sscanf(tokens[index].token.c_str(), "%d", &constant);
        string symbol = addConst(constant);
        ++index;
        return symbol;
    }
    if (tokens[index].type == TYPE_ID) {
        string symbol = tokens[index].token;
        if (!isSymbolExist(symbol)) {
            cerr << symbol << " is not defined." << endl;
        }
        ++index;
        return symbol;
    }
    cerr << "Expression should surrounded by parentheses." << endl;
    return "";
}

vector<Quaternion> getQuaternions(vector<Token> &tokens) {
    int index = 0;
    vector<Quaternion> quats;
    constIndex = 0;
    tempSymbolIndex = 0;
    symbolTable.clear();
    symbolMap.clear();
    labelIndex = 0;
    labelTable.clear();
    labelMap.clear();
    P(quats, tokens, index);
    return quats;
}

vector<SymbolNode> getSymbols() {
    return symbolTable;
}

vector<SymbolNode> getLabels() {
    return labelTable;
}

map<string, int> getSymbolMap() {
    return symbolMap;
}

map<string, int> getLabelMap() {
    return labelMap;
}

#ifdef DEBUG
void printQuaternions(vector<Quaternion> &quaternions) {
    cout << "Symbol Table: " << endl;
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        cout << i << "\t" << symbolTable[i].symbol << "\t";
        cout << symbolTable[i].value << endl;
    }
    cout << "Label Table: " << endl;
    for (size_t i = 0; i < labelTable.size(); ++i) {
        cout << i << "\t" << labelTable[i].symbol << "\t";
        cout << labelTable[i].value << endl;
    }
    cout << "Quaternions with symbol: " << endl;
    for (size_t i = 0; i < quaternions.size(); ++i) {
        Quaternion &quat = quaternions[i];
        cout << i << "\t" << quat.op << "\t";
        cout << quat.symbol1 << "\t";
        cout << quat.symbol2 << "\t";
        cout << quat.symbol3 << endl;
    }
    cout << "Quaternions with address: " << endl;
    for (size_t i = 0; i < quaternions.size(); ++i) {
        Quaternion &quat = quaternions[i];
        cout << i << "\t" << quat.op << "\t";
        cout << quat.addr1 << "\t";
        cout << quat.addr2 << "\t";
        cout << quat.addr3 << endl;
    }
}
#endif // DEBUG
