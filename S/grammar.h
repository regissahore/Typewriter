#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <vector>
#include <string>
#include "lex.h"

struct Quaternion
{
    std::string op;
    int src1;
    int src2;
    int dst;
};

std::vector<Quaternion> getQuaternions(std::vector<Token> &tokens);
#ifdef DEBUG
void printQuaternions(std::vector<Quaternion> &quaternions);
#endif // DEBUG

#endif // GRAMMAR_H_INCLUDED
