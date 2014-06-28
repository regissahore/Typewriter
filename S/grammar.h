#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <vector>
#include <string>
#include "lex.h"

struct Quaternion
{
    std::string op;
    std::string symbol1;
    std::string symbol2;
    std::string symbol3;
    int addr1;
    int addr2;
    int addr3;
};

std::vector<Quaternion> getQuaternions(std::vector<Token> &tokens);
#ifdef DEBUG
void printQuaternions(std::vector<Quaternion> &quaternions);
#endif // DEBUG

#endif // GRAMMAR_H_INCLUDED
