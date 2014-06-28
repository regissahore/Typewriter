#include <iostream>
#include "grammar.h"
using namespace std;

void P(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void D(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void S(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void L(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void L_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void B(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void T_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void F_(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void E(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void T(vector<Quaternion> &quats, vector<Token> &tokens, int &index);
void F(vector<Quaternion> &quats, vector<Token> &tokens, int &index);

void P(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "P" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    if (tokens[index].type == TYPE_L_BRACKET) {
        ++index;
        D(quats, tokens, index);
        L(quats, tokens, index);
    } else {
        cerr << "Program should start with '{'." << endl;
    }
}

void D(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "D" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    while (tokens[index].type == TYPE_INT) {
        ++index;
        if (tokens[index].type == TYPE_ID) {
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
    cout << index << "S" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    if (tokens[index].type == TYPE_IF) {
        ++index;
        if (tokens[index].type == TYPE_L_PARENTHESE) {
            ++index;
            B(quats, tokens, index);
            if (tokens[index].type == TYPE_R_PARENTHESE) {
                ++index;
                if (tokens[index].type == TYPE_THEN) {
                    ++index;
                    L(quats, tokens, index);
                    if (tokens[index].type == TYPE_ELSE) {
                        ++index;
                        L(quats, tokens, index);
                    }
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
        if (tokens[index].type == TYPE_L_PARENTHESE) {
            ++index;
            B(quats, tokens, index);
            if (tokens[index].type == TYPE_R_PARENTHESE) {
                ++index;
                if (tokens[index].type == TYPE_DO) {
                    ++index;
                    L(quats, tokens, index);
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
            cerr << "The brackets are mismatched." << endl;
        }
    } else if (tokens[index].type == TYPE_ID) {
        ++index;
        if (tokens[index].type == TYPE_ASSIGN) {
            ++index;
            E(quats, tokens, index);
        } else {
            cerr << "Should be assignment." << endl;
        }
    } else {
        cerr << "Invalid statement." << endl;
    }
}

void L(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "L" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    S(quats, tokens, index);
    L_(quats, tokens, index);
}

void L_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "L'" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    if (tokens[index].type == TYPE_SEMICOLON) {
        ++index;
        L(quats, tokens, index);
    }
}

void B(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "B" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    T_(quats, tokens, index);
    if (tokens[index].type == TYPE_OR) {
        ++index;
        T_(quats, tokens, index);
    }
}

void T_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "T'" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    F_(quats, tokens, index);
    if (tokens[index].type == TYPE_AND) {
        ++index;
        F_(quats, tokens, index);
    }
}

void F_(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "F'" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    F(quats, tokens, index);
    if (tokens[index].type == TYPE_RELOP) {
        ++index;
        F(quats, tokens, index);
    }
}

void E(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "E" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    T(quats, tokens, index);
    if (tokens[index].type == TYPE_ADD) {
        ++index;
        T(quats, tokens, index);
    } else if (tokens[index].type == TYPE_SUB) {
        ++index;
        T(quats, tokens, index);
    }
}

void T(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "T" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    F(quats, tokens, index);
    if (tokens[index].type == TYPE_MUL) {
        ++index;
        F(quats, tokens, index);
    } else if (tokens[index].type == TYPE_DIV) {
        ++index;
        F(quats, tokens, index);
    }
}

void F(vector<Quaternion> &quats, vector<Token> &tokens, int &index) {
    cout << index << "F" << tokens[index].type << " " << tokens[index].mnemonic << " " << tokens[index].token << endl;
    if (tokens[index].type == TYPE_L_PARENTHESE) {
        ++index;
        E(quats, tokens, index);
        if (tokens[index].type == TYPE_R_PARENTHESE) {
            ++index;
        } else {
            cerr << "The parentheses are mismatched." << endl;
        }
    } else if (tokens[index].type == TYPE_CONST) {
        ++index;
    } else if (tokens[index].type == TYPE_ID) {
        ++index;
    } else {
        cerr << "Expression should surrounded by parentheses." << endl;
    }
}

vector<Quaternion> getQuaternions(vector<Token> &tokens) {
    int index = 0;
    vector<Quaternion> quats;
    P(quats, tokens, index);
    return quats;
}

#ifdef DEBUG
void printQuaternions(vector<Quaternion> &quaternions) {
}
#endif // DEBUG
