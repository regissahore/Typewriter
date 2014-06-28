#include <iostream>
#include "lex.h"
using namespace std;

bool isAlphabeta(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

string getTokenString(string &buffer, int &prev, int index) {
    int temp = prev;
    prev = index;
    return buffer.substr(temp, index - temp);
}

void parse(vector<Token> &tokens, string &buffer) {
    int state = 0, index = 0, prev = 0;
    buffer += (char)0;
    while (true) {
        char ch = buffer[index];
        switch (state) {
        case 0:
            if (isAlphabeta(ch)) {
                ++index;
                state = 1;
            } else if (isDigit(ch)) {
                ++index;
                state = 3;
            } else {
                switch (ch) {
                case '+':
                    prev = ++index;
                    tokens.push_back({TYPE_ADD, "+", ""});
                    break;
                case '-':
                    prev = ++index;
                    tokens.push_back({TYPE_SUB, "-", ""});
                    break;
                case '*':
                    prev = ++index;
                    tokens.push_back({TYPE_MUL, "*", ""});
                    break;
                case '/':
                    prev = ++index;
                    tokens.push_back({TYPE_DIV, "/", ""});
                    break;
                case '&':
                    prev = ++index;
                    tokens.push_back({TYPE_AND, "and", ""});
                    break;
                case '|':
                    prev = ++index;
                    tokens.push_back({TYPE_OR, "or", ""});
                    break;
                case '{':
                    prev = ++index;
                    tokens.push_back({TYPE_L_BRACKET, "{", ""});
                    break;
                case '}':
                    prev = ++index;
                    tokens.push_back({TYPE_R_BRACKET, "}", ""});
                    break;
                case ';':
                    prev = ++index;
                    tokens.push_back({TYPE_SEMICOLON, ";", ""});
                    break;
                case '(':
                    prev = ++index;
                    tokens.push_back({TYPE_L_PARENTHESE, "(", ""});
                    break;
                case ')':
                    prev = ++index;
                    tokens.push_back({TYPE_R_PARENTHESE, ")", ""});
                    break;
                case '<':
                case '>':
                case '!':
                    ++index;
                    state = 6;
                    break;
                case '=':
                    ++index;
                    state = 9;
                    break;
                case ' ':
                case 0:
                    prev = ++index;
                    break;
                default:
                    ++index;
                    cerr << "Invalid character: " << getTokenString(buffer, prev, index) << endl;
                    break;
                }
            }
            break;
        case 1:
            if (isAlphabeta(ch) || isDigit(ch)) {
                ++index;
            } else {
                state = 0;
                string token = getTokenString(buffer, prev, index);
                if (token == string("int")) {
                    tokens.push_back({TYPE_INT, "int", ""});
                } else if (token == string("if")) {
                    tokens.push_back({TYPE_IF, "if", ""});
                } else if (token == string("then")) {
                    tokens.push_back({TYPE_THEN, "then", ""});
                } else if (token == string("else")) {
                    tokens.push_back({TYPE_ELSE, "else", ""});
                } else if (token == string("while")) {
                    tokens.push_back({TYPE_WHILE, "while", ""});
                } else if (token == string("do")) {
                    tokens.push_back({TYPE_DO, "do", ""});
                } else if (token == string("read")) {
                    tokens.push_back({TYPE_READ, "read", ""});
                } else if (token == string("write")) {
                    tokens.push_back({TYPE_WRITE, "write", ""});
                } else {
                    tokens.push_back({TYPE_ID, "ID", token});
                }
            }
            break;
        case 3:
            if (isDigit(ch)) {
                ++index;
            } else {
                state = 0;
                tokens.push_back({TYPE_CONST, "NUM", getTokenString(buffer, prev, index)});
            }
            break;
        case 6:
            state = 0;
            if (ch == '=') {
                ++index;
                tokens.push_back({TYPE_RELOP, "relop", getTokenString(buffer, prev, index)});
            } else {
                if (buffer[prev] != '!') {
                    tokens.push_back({TYPE_RELOP, "relop", getTokenString(buffer, prev, index)});
                } else {
                    cerr << "Invalid Character: '!'" << endl;
                }
            }
            break;
        case 9:
            state = 0;
            if (ch == '=') {
                ++index;
                tokens.push_back({TYPE_RELOP, "relop", getTokenString(buffer, prev, index)});
            } else {
                prev = index;
                tokens.push_back({TYPE_ASSIGN, "=", ""});
            }
            break;
        }
        if (ch == 0) {
            break;
        }
    }
}

vector<Token> getTokens() {
    int lineNum = 0;
    string buffer;
    vector<Token> tokens;
    while (getline(cin, buffer)) {
        ++lineNum;
        parse(tokens, buffer);
    }
    return tokens;
}

#ifdef DEBUG
void printTokens(vector<Token> &tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token &token = tokens[i];
        cout << i << "\t";
        cout << token.type << "\t" << token.mnemonic << "\t";
        if (token.token.length() > 0) {
            cout << token.token << endl;
        } else {
            cout << "---" << endl;
        }
    }
}
#endif // DEBUG
