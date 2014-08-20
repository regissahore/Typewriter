#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

#include <string>
#include <vector>
#include "grammar.h"

void printAssembly(std::vector<Quaternion> &quats,
                   std::map<std::string, int> &symbolMap,
                   std::vector<SymbolNode> &symbolTable,
                   std::map<std::string, int> &labelMap,
                   std::vector<SymbolNode> &labelTable);

#endif // ASM_H_INCLUDED
