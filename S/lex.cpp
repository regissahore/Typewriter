#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
const int BUFFER_LEN = 1024;
const int TOKEN_LEN = 32;

#define DEBUG

enum TokenType {
    TYPE_INT = 1,
    TYPE_IF = 2,
    TYPE_THEN = 3,
    TYPE_ELSE = 4,
    TYPE_WHILE = 5,
    TYPE_DO = 6,
    TYPE_ID = 7,
    TYPE_CONST = 8,
    TYPE_ADD = 9,
    TYPE_SUB = 10,
    TYPE_MUL = 11,
    TYPE_DIV = 12,
    TYPE_AND = 13,
    TYPE_OR = 14,
    TYPE_RELOP = 15,
    TYPE_L_BRACKET = 16,
    TYPE_R_BRACKET = 17,
    TYPE_SEMICOLON = 18,
    TYPE_L_PARENTHESE = 19,
    TYPE_R_PARENTHESE = 20,
    TYPE_ASSIGN = 21
};

struct Token {
    TokenType type;
    string mnemonic;
    string token;
};

bool isAlphabeta(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

string getTokenString(char buffer[BUFFER_LEN], int &prev, int index) {
    static char temp[BUFFER_LEN];
    for (int i = prev; i < index; ++i) {
        temp[i - prev] = buffer[i];
    }
    temp[index - prev] = 0;
    prev = index;
    return string(temp);
}

void parse(vector<Token> &tokens, char buffer[BUFFER_LEN]) {
    int state = 0, index = 0, prev = 0;
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
                    fprintf(stderr, "Invalid Character: ");
                    fprintf(stderr, getTokenString(buffer, prev, index).c_str());
                    fprintf(stderr, "\n");
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
                    fprintf(stderr, "Invalid Character: !\n");
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

int main() {
    int lineNum = 0;
    char buffer[BUFFER_LEN];
    vector<Token> tokens;
    while (gets(buffer)) {
        ++lineNum;
        parse(tokens, buffer);
    }
    #ifdef DEBUG
    for (auto token : tokens) {
        cout << token.type << "\t" << token.mnemonic << "\t";
        if (token.token.length() > 0) {
            cout << token.token << endl;
        } else {
            cout << "---" << endl;
        }
    }
    #endif // DEBUG
    return 0;
}
