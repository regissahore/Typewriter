#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <map>
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

struct SymbolNode {
    std::string symbol;
    int value;
};

std::vector<Quaternion> getQuaternions(std::vector<Token> &tokens);
std::vector<SymbolNode> getSymbols();
std::map<std::string, int> getSymbolMap();
std::vector<SymbolNode> getLabels();
std::map<std::string, int> getLabelMap();
#ifdef DEBUG
void printQuaternions(std::vector<Quaternion> &quaternions);
#endif // DEBUG

#endif // GRAMMAR_H_INCLUDED
