#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED

#include <string>
#include <vector>

enum TokenType {
    TYPE_INT = 1,
    TYPE_IF, TYPE_THEN, TYPE_ELSE, TYPE_WHILE, TYPE_DO,
    TYPE_ID, TYPE_CONST,
    TYPE_ADD, TYPE_SUB, TYPE_MUL, TYPE_DIV,
    TYPE_AND, TYPE_OR, TYPE_RELOP,
    TYPE_L_BRACKET, TYPE_R_BRACKET,
    TYPE_SEMICOLON,
    TYPE_L_PARENTHESE, TYPE_R_PARENTHESE,
    TYPE_ASSIGN, TYPE_READ, TYPE_WRITE
};

struct Token {
    TokenType type;
    std::string mnemonic;
    std::string token;
};

std::vector<Token> getTokens();
void printTokens(std::vector<Token> &tokens);

#endif // LEX_H_INCLUDED
